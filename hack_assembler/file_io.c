#include "file_io.h"

// just a copy of "parse" from parser.c
int read(FILE* in, DATA data)
{
	char line[LINE_LEN] = { 0 };
	int instruction_count = 0, symbols_register = 16; // we use this register for user defined symbols

	while (fgets(line, LINE_LEN - 1, in))
	{
		// read lines to data
		// clear spaces and '\n' from line
		if (DEBUG_LINE_CLEANUP)
			printf("line:\n%s\n", line);

		if (clean_line(line))
		{
			if (DEBUG_LINE_CLEANUP)
				printf("cleaned line:\n%s\n", line);

			// if the symbol is used-defined (@i for example), we just set it to symbols_register
			// and increment it for the next time, we won't run out until 16381 or thereabouts
			if (line[0] == '@')
				load_A_instruction(line, &data[instruction_count++], &symbols_register);

			// we ignore labels as they are already defined in out dictionary
			else if (!(line[0] == '('))
				load_C_instruction(line, &data[instruction_count++]);
		}
	}
	return instruction_count;
}

void write(FILE* out, DATA data, int no_of_instructions)
{
	int i;
	char binary[17], dest[4], comp[8], jump[4]; // the last 3 could be used for verbose printing
	for (i = 0; i < no_of_instructions; i++)
	{
		// write each istruction to hack file
		integer_to_binary(data[i].binary, binary, data[i].type == 'C', 16); // 16 is the width of a
																			// word in HACK
		fprintf(out, "%s\n", binary);

		if (VERBOSE_TRANSLATION) {
			// define binary form of each part of a C instruction
			if (data[i].type == 'C') {
				integer_to_binary(data[i].parts[0], comp, 0, 7);
				integer_to_binary(data[i].parts[1], dest, 0, 3);
				integer_to_binary(data[i].parts[2], jump, 0, 3);
				printf("Instruction %d:  type:%c  comp: %s  dest: %s  jump: %s  \nFinal binary: %s\n\n",
					i, data[i].type, comp, dest, jump, binary);
			}
			else
				printf("Instruction %d:  type: %c\nnFinal binary: %s\n\n",
					i, data[i].type, binary);

		}
	}
}

// set bin to a string of 0s and 1s according to the value of n, of size of n digits
// set left parameter is used to handle the peculiarities of the hack machine code
void integer_to_binary(int n, char* bin, bool setLeft, int digits)
{
	int i = digits - 1;
	if (bin) {
		bin[digits] = '\0';
		while (i >= 0)
		{
			bin[i--] = (n & 1) ? '1' : '0';
			n = n >> 1;
		}
		if (setLeft)
		{
			bin[0] = bin[1] = bin[2] = '1';
		}
	}
}

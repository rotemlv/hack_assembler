#include "parser.h"

bool is_numeric(char* word)
{
	while (*word != 0)
	{
		if ((*word) > '9' || (*word) < '0')
			return false;
		word++;
	}
	return true;
}

Entry lookup_instruction_in_dict(Dictionary dict, char* word, int wordSize)
{
	int i;
	Entry entry = { .inst = "",.binary = -1 };
	for (i = 0; i < dict.size; i++)
	{
		if (wordSize == strlen(dict.dictionary[i].inst) &&
			strncmp(dict.dictionary[i].inst, word, wordSize) == 0)
			return dict.dictionary[i];
		//printf("%s, %s, %d, %d\n", word, dict.dictionary[i].inst, wordSize, strlen(dict.dictionary[i].inst));

	}

	return entry; // error
}

// just in case we need this:
Entry compare_binary_with_dict(Dictionary dict, char* word, int wordSize)
{
	int i;
	Entry entry = { .inst = "",.binary = -1 };
	for (i = 0; i < dict.size; i++)
	{
		if (wordSize == strlen(dict.dictionary[i].inst) &&
			strncmp(dict.dictionary[i].inst, word, wordSize) == 0)
			return dict.dictionary[i];

	}

	return entry; // error
}


void load_A_instruction(char* line, Instruction* instruction, int *symbols_register)
{
	int binary;
	char* linepp = line + 1;
	// initial instruction properties
	instruction->type = 'A';
	instruction->symbol = false;
	// not a symbol
	if(is_numeric(linepp))
		instruction->binary = atoi(linepp); // we keep it as base 10 for now
	else
	{
		binary = lookup_instruction_in_dict(symbols, linepp, strlen(linepp)).binary;
		// look for instruction in symbols dictionary:
		if (binary == -1)
		{
			// we load the instruction from dict!
			append_symbol(&symbols, line, *symbols_register);
			instruction->binary = (*symbols_register);

			// for next time:
			(*symbols_register)++;
		}
		else
		{
			// we load binary to the instruction
			instruction->binary = binary;
		}

		instruction->symbol = true; // we probably wont need this
	}
}

// i herd you like compact functions
void whichCINST(int* d, int* c, int* j, char* line, char* eq, char* smc)
{
	// diff:
	if (eq)
	{
		// dest is before equals
		*d = lookup_instruction_in_dict(dest, line, eq - line).binary; // X=Y -> get the X
		*c = lookup_instruction_in_dict(comp, eq+1, (smc) ? smc - eq - 1 : strlen(eq+1)).binary; // X=Y -> get the Y
		*j = lookup_instruction_in_dict(jump, (smc)?smc+1:"", (smc)?strlen(smc+1):0).binary;

	}
	else
	{
		// no dest, only comp maybe jump
		*c = lookup_instruction_in_dict(comp, line, (smc) ? smc - line : strlen(line)).binary; // X=Y -> get the Y
		*j = lookup_instruction_in_dict(jump, (smc) ? smc+1 : "", (smc) ? strlen(smc+1) : 0).binary;

	}
}

void load_C_instruction(char* line, Instruction* instruction)
{
	char* eq_pointer = strchr(line, '='), * semicolon_pointer = strchr(line, ';');
	int dst = 0, cmp = 0, jmp = 0;

	// set type
	instruction->type = 'C';

	// set parts
	whichCINST(&dst, &cmp, &jmp, line,eq_pointer, semicolon_pointer); 
	// debug - if we failed reading this instruction, exit (for now)
	if (dst == -1 || cmp == -1 || jmp == -1)
	{
		printf("Error parsing a C instruction in line %s\nExiting . . . ", line);
		exit(-1);
	}

	// set binary (without the 111 "prefix"):
	// 111 a c1 c.. c6 d1 d2 d3 j1 j2 j3
	instruction->binary = (jmp)+(dst << 3) + (cmp << 6);

	// for debug purposes:
	instruction->parts[0] = cmp;
	instruction->parts[1] = dst;
	instruction->parts[2] = jmp;

	instruction->symbol = false; // not needed


}

int initial_parse(FILE* in, Dictionary *symbols)
{
	// count lines, if (label) found, place label in symbols dictionary, with line count as instruction
	char line[LINE_LEN];
	int i = 0;
	while (fgets(line, LINE_LEN - 1, in))
	{
		if (DEBUG_LINE_CLEANUP)
			printf("line: \n%s\n", line);

		if (clean_line(line))
		{
			// we got a line (no legality check)
			// if we want to check for legal characters, this is the place
			// 
			// if we are at a label, insert symbol with label name, and binary value of i (current inst)

			if(DEBUG_LINE_CLEANUP)
				printf("cleaned line: \n%s\n", line);
			if (line[0] == '(')
				append_label(symbols, line, i);	// we do not count labels as lines
			else
				i++;	// increment i
		}
	}
	return 0;
}


int parse(FILE* in, DATA data)
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
			else if(!(line[0] == '('))
				load_C_instruction(line, &data[instruction_count++]);
		}
	}
	return instruction_count;
}

// stack overflow implementation - not in use
bool clean_forbidden_characters(char* line) {
	char* linePtr = line, *orig = line;
	do {
		while (*linePtr == ' ' || *linePtr == '\t' || *linePtr == '\n') {
			++linePtr; // increment line pointer as long as its on a forbidden character
		}
	} while (*line++ = *linePtr++); // set line to line pointer and keep checking as long as its not null
	return strlen(orig) > 0; // check emptiness of the line
}

bool clean_line(char* line)
{
	int i = 0, j = 0, n = strlen(line);
	char tmp[LINE_LEN] = { '\0' };

	// prepare
	strcpy(tmp, line);
	// clean
	while (i < n)
	{
		// comment after instruction
		if (tmp[i] == '/')
		{
			if (i + 1 < n && tmp[i + 1] == '/')
				i = n; // we stop reading
			else
			{
				// bad instruction ends with "/", not "//" (the only invalid input I test)
				printf("\nBAD ISTRUCTION IN FILE, %s\n", tmp);
				exit(1);
				// this WILL create a memory leak now! solution: return int and use a boolean pointer, or just use 0,1,-1 for f,t,err
			}
		}
		else if (tmp[i] == ' ' || tmp[i] == '\n' || tmp[i] == '\t')
			i++;
		else
			line[j++] = tmp[i++];

	}
	// empty line case, place null where needed
	line[j] = '\0';

	return strlen(line) > 0;
}
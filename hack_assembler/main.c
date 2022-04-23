#include "headers.h"
#include "globals.h"
#include "parser.h"
#include "file_io.h"

void run_app_from_exe();
void run_app_from_console(char* arg1, char* arg2);
#include<stdio.h> 

#include<stdlib.h> 

#include<string.h> 



int main(int argc, char* argv[])

{

	if (argc != 2 || strlen(argv[1]) == 0)

	{

		printf("Error: %d parameter(s) sent to main\n", (argc == 2) ? 1 : argc);

		exit(1); // we can only receive one parameter - the string 

	}



	char* p = argv[1], c;

	// show argv[1] to screen in uppercase, with '@' as a line delimiter 

	while (*p)

	{



		c = *p;

		if (*p >= 'a' && *p <= 'z')

			c = (*p) - 32;

		(c == '@') ? printf("\n") : printf("%c", c);

		p++;

	}

	printf("\n");
	return 0;
}

main(int argc, char *argv[])
{
	char* out;
	int n;
	printf("CURRENT C INSTRUCTION PARSE IS EXPERIMENTAL, FOR VERIFIED RESULTS USE "
		"THE which_C_instruction FUNCTION CALL (it's probably fine, but I can't be bothered)\n");
	printf("* Listen carefully as it's very important," // jamesu vilson quote
		"\n  This program is not to be used anywhere a possibility of remote access is present.\n"
		"  The scanf-calls will allow buffer overflow, with all the vulnerabilities it comes with! *\n\n");
	if (argc < 2)
		run_app_from_exe();
	// fill this, allow argv[1] to be the input file, and argv[2] output
	// if exists, 
	else if(argc > 2)
		run_app_from_console(argv[1], argv[2]);

	// else create output as argv[1] but with the .hack extension instead of asm
	else
	{
		n = strlen(argv[1]);
		out = calloc((n+12), sizeof * out);  // TODO: this should be on the stack, though
		if (out == NULL)
		{
			printf("Allocation failure in main\n");
			exit(1);
		}
		strncpy(out, argv[1],n - 4);  // this does not null terminate the ting
		out[n - 4] = '\0';
		strcat(out, ".hack");
		run_app_from_console(argv[1], out);

	}


}

void run_app_from_console(char* arg1, char* arg2)
{
	FILE* f_in, * f_out;

	f_in = fopen(arg1, "r");
	if (f_in == NULL)
	{
		printf("Input file doesn't exist.\n");
		exit(1);
	}
	// data is a mere Instruction struct pointer, it has been moved to the heap (as it's large)
	DATA data = calloc(LINE_COUNT, sizeof data);
	if (data == NULL)
	{
		perror("Allocation error in main\n");

		// if it runs from console
		_getch();

		exit(1);
	}

	// extended symbols dict has been moved to the heap too
	Entry* extended_symbols_dictionary = calloc(TOTAL_SYMBOLS_COUNT,
		sizeof * extended_symbols_dictionary);

	if (extended_symbols_dictionary == NULL)
	{
		perror("Allocation error in main\n");
		free(data);


		// if it runs from console
		_getch();

		exit(1);
	}

	// this call doesn't check for sizes, new dict here has to have the same or greater size
	load_symbols_to_extended_dict(symbols, extended_symbols_dictionary);
	symbols.dictionary = extended_symbols_dictionary;

	// initial parse - load symbols to dictionary from labels
	initial_parse(f_in, &symbols);

	// rewind to beginning
	fseek(f_in, 0, SEEK_SET);

	// now we got proper symbols in dict
	// parse proper
	int data_size = parse(f_in, data);

	fclose(f_in);

	f_out = fopen(arg2, "w");
	write(f_out, data, data_size);

	fclose(f_out);

	printf("File %s succesfully converted to HACK."
		"Output: %s\nPress the \"ANY\" key to close . . .", arg1,arg2);

	free(data);
	free(extended_symbols_dictionary);

	_getch();
}

void run_app_from_exe()
{
	FILE* f_in, * f_out;
	char input_file_name[MAX_FILE_NAME_LEN] = { 0 }, output_file_name[MAX_FILE_NAME_LEN + 5] = { 0 };
	printf("Enter input file (.asm): >");
	if (scanf("%s", input_file_name) != 1)
	{
		printf("Invalid input!\n");

		// if it runs from console
		_getch();

		exit(1);
	}

	rewind(stdin); // replace this with something better

	f_in = fopen(input_file_name, "r");

	if (f_in == NULL)
	{
		printf("Input file (%s) not found!\n", input_file_name);


		// if it runs from console
		_getch();

		exit(1);


	}

	printf("\nEnter output file name (no need for the .hack suffix): >");
	if (scanf("%s", output_file_name) != 1)
	{
		printf("Invalid input!\n");

		// if it runs from console
		_getch();


		exit(1);
	}
	strcat(output_file_name, ".hack");

	// data is a mere Instruction struct pointer, it has been moved to the heap (as it's large)
	DATA data = calloc(LINE_COUNT, sizeof data);
	if (data == NULL)
	{
		perror("Allocation error in main\n");

		// if it runs from console
		_getch();

		exit(1);
	}

	// extended symbols dict has been moved to the heap too
	Entry* extended_symbols_dictionary = calloc(TOTAL_SYMBOLS_COUNT,
		sizeof * extended_symbols_dictionary);

	if (extended_symbols_dictionary == NULL)
	{
		perror("Allocation error in main\n");
		free(data);


		// if it runs from console
		_getch();

		exit(1);
	}

	// this call doesn't check for sizes, new dict here has to have the same or greater size
	load_symbols_to_extended_dict(symbols, extended_symbols_dictionary);
	symbols.dictionary = extended_symbols_dictionary;

	// initial parse - load symbols to dictionary from labels
	initial_parse(f_in, &symbols);

	// rewind to beginning
	fseek(f_in, 0, SEEK_SET);

	// now we got proper symbols in dict
	// parse proper
	int data_size = parse(f_in, data);

	fclose(f_in);

	// write to file

	f_out = fopen(output_file_name, "w");

	write(f_out, data, data_size);

	fclose(f_out);
	printf("File %s succesfully converted to HACK."
		"Output: %s\nPress the \"ANY\" key to close . . .", input_file_name, output_file_name);

	// free dynamic allocations
	free(extended_symbols_dictionary);
	free(data);


	// if it runs from console
	_getch();

}

// an option, load to heap:

	/*Entry* extended_symbols_dictionary = calloc(TOTAL_SYMBOLS_COUNT,
		sizeof * extended_symbols_dictionary);
	*/

/*
* 
	// test:
printf("The symbols dictionary after append:\n");
for (int i = 0; i < symbols.size; i++)
	printf("symbol: %s, %d\n", symbols.dictionary[i].inst, symbols.dictionary[i].binary);

*/
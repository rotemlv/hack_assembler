#ifndef _HEADERS
#define _HEADERS

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// just used for UI
#include <conio.h>
#include <ctype.h>

// debug functionalities

#define VERBOSE_TRANSLATION 0  // boolean: print each instruction during write
#define DEBUG_LINE_CLEANUP 0   // boolean: print lines before and after cleanup

// sizes

#define SYMBOLS_COUNT 23    // standard symbols only
#define COMP_INST_COUNT 34
#define JUMP_INST_COUNT 8
#define DEST_INST_COUNT 8

#define COMP_INSTRUCTION_WIDTH 7 // these 3 are only for logging
#define DEST_INSTRUCTION_WIDTH 3
#define JUMP_INSTRUCTION_WIDTH 3 

#define LINE_LEN 160		   // total characters ( + 1) in each line in input.asm file
#define LINE_COUNT 1000        // total lines in input.asm file
#define MAX_INSTRUCTION_LEN 64 // just to be extra, extra safe

#define MAX_FILE_NAME_LEN 30 // not in use atm

#define TOTAL_SYMBOLS_COUNT 1000

typedef struct Entry {
	char inst[MAX_INSTRUCTION_LEN];
	int binary;
}Entry;

typedef struct Dictionary {
	Entry* dictionary;   // each entry in the assembler dictionary
	int size;			 // how many entries exist in the dictionary
}Dictionary;

typedef struct Instruction {
	char type; // A or C
	int binary; // 16 LSD are the instruction

	int parts[3]; // for debug, keeps comp,dest,jump parts of a C inst, where the 'a' bit is in comp
	bool symbol;  // can be used for debugging
}Instruction;

typedef Instruction *DATA; // defined as an array of instructions



#endif
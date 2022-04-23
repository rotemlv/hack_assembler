#ifndef _PARSER
#define _PARSER

#include"headers.h"
#include"globals.h"

void load_A_instruction(char* line, Instruction* instruction, int * symbols_register);
void load_C_instruction_OLD(char* line, Instruction* instruction); // discard
void load_C_instruction(char* line, Instruction* instruction);

void whichCINST(int* d, int* c, int* j, char* line, char* eq, char* smc); // new idea
void which_C_instruction(int* d, int* c, int* j, char* line, char* eq, char* smc);

int initial_parse(FILE* in, Dictionary *symbols);
int parse(FILE* in, DATA data);

bool clean_line(char* line);
bool is_numeric(char* word);


// testing
bool clean_forbidden_characters(char* line);

Entry compare_binary_with_dict(Dictionary dict, char* word, int wordSize);
Entry lookup_instruction_in_dict(Dictionary dict, char* word, int wordSize);

#endif
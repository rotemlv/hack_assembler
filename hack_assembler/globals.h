#ifndef _GLOBALS
#define _GLOBALS

#include "headers.h"

// this file maintains all global variables used in creating this assembler (sadly there are many)

Entry symbols_dict[SYMBOLS_COUNT];
Entry comp_dict[COMP_INST_COUNT];
Entry dest_dict[DEST_INST_COUNT];
Entry jump_dict[JUMP_INST_COUNT];
Dictionary comp;
Dictionary dest;
Dictionary jump;
Dictionary symbols;

void append_label(Dictionary *symbols, char* word, int binary);
void append_symbol(Dictionary* symbols, char* word, int binary);
void load_symbols_to_extended_dict(Dictionary olddict, Entry* newdict);

#endif
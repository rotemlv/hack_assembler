#ifndef _FILE_IO
#define _FILE_IO

#include "headers.h"
#include "globals.h"
#include "parser.h"

void write(FILE* out, DATA data, int instruction_count);

// currently it's just a copy of 'parse' from parser.c, use better names and factorization
int read(FILE* in, DATA data);

void integer_to_binary(int n, char* bin, bool setLeft, int digits);

#endif
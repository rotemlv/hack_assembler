#include "globals.h"

Entry symbols_dict[] =
{
	[0] .inst = "R0",[0].binary = 0b0,
	[1].inst = "R1",[1].binary = 0b1,
	[2].inst = "R2",[2].binary = 0b10,
	[3].inst = "R3",[3].binary = 0b11,
	[4].inst = "R4",[4].binary = 0b100,
	[5].inst = "R5",[5].binary = 0b101,
	[6].inst = "R6",[6].binary = 0b110,
	[7].inst = "R7",[7].binary = 0b111,
	[8].inst = "R8",[8].binary = 0b1000,
	[9].inst = "R9",[9].binary = 0b1001,
	[10].inst = "R10",[10].binary = 0b1010,
	[11].inst = "R11",[11].binary = 0b1011,
	[12].inst = "R12",[12].binary = 0b1100,
	[13].inst = "R13",[13].binary = 0b1101,
	[14].inst = "R14",[14].binary = 0b1110,
	[15].inst = "R15",[15].binary = 0b1111,
	[16].inst = "SP",[16].binary = 0b0,
	[17].inst = "LCL",[17].binary = 0b1,
	[18].inst = "ARG",[18].binary = 0b10,
	[19].inst = "THIS",[19].binary = 0b11,
	[20].inst = "THAT",[20].binary = 0b100,
	[21].inst = "SCREEN",[21].binary = 0x4000,
	[22].inst = "KBD",[22].binary = 0x6000

};

// we should probably add an option to use A+D and D+A not just one (ADDED)
Entry comp_dict[34] =
{
	// add duplicates for edge cases (D=M+D, D=D+M are both possible in our asm)
	[0] .inst = "0",[0].binary = 0b0101010,
	[1].inst = "1",[1].binary = 0b0111111,
	[2].inst = "-1",[2].binary = 0b0111010,
	[3].inst = "D",[3].binary = 0b0001100,
	[4].inst = "A",[4].binary = 0b0110000,
	[5].inst = "M",[5].binary = 0b1110000,
	[6].inst = "!D",[6].binary = 0b0001101,
	[7].inst = "!A",[7].binary = 0b0110001,
	[8].inst = "!M",[8].binary = 0b1110001,
	[9].inst = "-D",[9].binary = 0b0001111,
	[10].inst = "-A",[10].binary = 0b0110011,
	[11].inst = "-M",[11].binary = 0b1110011,
	[12].inst = "D+1",[12].binary = 0b0011111,
	[13].inst = "A+1",[13].binary = 0b0110111,
	[14].inst = "M+1",[14].binary = 0b1110111,
	[15].inst = "D-1",[15].binary = 0b0001110,
	[16].inst = "A-1",[16].binary = 0b0110010,
	[17].inst = "M-1",[17].binary = 0b1110010,
	[18].inst = "D+A",[18].binary = 0b0000010,
	[19].inst = "D+M",[19].binary = 0b1000010,
	[20].inst = "D-A",[20].binary = 0b0010011,
	[21].inst = "D-M",[21].binary = 0b1010011,
	[22].inst = "A-D",[22].binary = 0b0000111,
	[23].inst = "M-D",[23].binary = 0b1000111,
	[24].inst = "D&A",[24].binary = 0b0000000,
	[25].inst = "D&M",[25].binary = 0b1000000,
	[26].inst = "D|A",[26].binary = 0b0010101,
	[27].inst = "D|M",[27].binary = 0b1010101,

	[28].inst = "A+D",[28].binary = 0b0000010,
	[29].inst = "M+D",[29].binary = 0b1000010,
	[30].inst = "D&A",[30].binary = 0b0000000,
	[31].inst = "D&M",[31].binary = 0b1000000,
	[32].inst = "D|A",[32].binary = 0b0010101,
	[33].inst = "D|M",[33].binary = 0b1010101,

};

Entry dest_dict[8] =
{
	[0] .inst = "",[0].binary = 0b000,
	[1].inst = "M",[1].binary = 0b001,
	[2].inst = "D",[2].binary = 0b010,
	[3].inst = "MD",[3].binary = 0b011, // same here
	[4].inst = "A",[4].binary = 0b100,
	[5].inst = "AM",[5].binary = 0b101,
	[6].inst = "AD",[6].binary = 0b110,
	[7].inst = "AMD",[7].binary = 0b111 // ADM OR AMD, in my book its the latter

};

Entry jump_dict[8] =
{
	[0] .inst = "",[0].binary = 0b000,
	[1].inst = "JGT",[1].binary = 0b001,
	[2].inst = "JEQ",[2].binary = 0b010,
	[3].inst = "JGE",[3].binary = 0b011,
	[4].inst = "JLT",[4].binary = 0b100,
	[5].inst = "JNE",[5].binary = 0b101,
	[6].inst = "JLE",[6].binary = 0b110,
	[7].inst = "JMP",[7].binary = 0b111

};

Dictionary comp = { .dictionary = comp_dict,     .size = COMP_INST_COUNT };
Dictionary dest = { .dictionary = dest_dict,     .size = DEST_INST_COUNT };
Dictionary jump = { .dictionary = jump_dict,     .size = JUMP_INST_COUNT };
Dictionary symbols = { .dictionary = symbols_dict,  .size = SYMBOLS_COUNT };

// these two functions could very easily be one, lazy bum
void append_label(Dictionary *symbols, char* word, int binary)
{
	// get word[1:-1]
	char* appendThis = word + 1;
	// copy name:
	strncpy(symbols->dictionary[symbols->size].inst, appendThis, strlen(appendThis) - 1);
	symbols->dictionary[symbols->size].inst[strlen(appendThis) - 1] = '\0'; // fix escape char
	symbols->dictionary[symbols->size].binary = binary;

	symbols->size++;

}

void append_symbol(Dictionary* symbols, char* word, int binary)
{
	// get word[1:-1]
	char* appendThis = word + 1;
	// copy name:
	strcpy(symbols->dictionary[symbols->size].inst, appendThis);
	symbols->dictionary[symbols->size].binary = binary;

	symbols->size++;

}

// set new dictionary to the old one, used for extended symbols as we can't know how many there'll be
// And I really don't like it being on the stack
void load_symbols_to_extended_dict(Dictionary olddict, Entry* newdict)
{
	int i;
	for (i = 0; i < olddict.size; i++)
		newdict[i] = olddict.dictionary[i];
}

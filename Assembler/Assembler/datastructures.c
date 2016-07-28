#ifndef LABEL_LENGTH
#define LABEL_LENGTH 30
#endif

typedef struct Symbol {
	char label[LABEL_LENGTH];
	int counter;
	int content;
	SymbolType type;
	Symbol *next;
	
} Symbol;

typedef enum SymbolType {
	Code, Data
} SymbolType;

typedef enum Register {
	r1, r2, r3, r4, r5, r6
} Register;

typedef union operand {
	int number;
	char label[LABEL_LENGTH];
	Register reg;
} operand;
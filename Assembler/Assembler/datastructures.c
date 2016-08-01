#ifndef LABEL_LENGTH
#define LABEL_LENGTH 30
#endif

typedef struct Symbol {
	char label[LABEL_LENGTH];
	int counter;
	int content;
	enum SymbolType type;
	struct Symbol *next;
	
} Symbol;

typedef enum SymbolType {
	Code, Data
} SymbolType;

typedef enum Register {
	r1, r2, r3, r4
} Register;

typedef union operand {
	int number;
	char label[LABEL_LENGTH];
	Register reg;
} operand;
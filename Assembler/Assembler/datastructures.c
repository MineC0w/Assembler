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

typedef enum {
	Code, Data
} SymbolType;
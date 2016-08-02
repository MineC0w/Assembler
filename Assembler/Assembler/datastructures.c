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

typedef union OperandData {
	int number;
	char label[LABEL_LENGTH];
	Register reg;
} OperandData;

typedef enum OperandType {
	Reg, Number, Label
} OperandType;

typedef struct operand {
	OperandType type;
	OperandData data;
} operand;


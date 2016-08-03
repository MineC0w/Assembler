#pragma once

#ifndef datastructures_h 
#define datastructures_h

#define LABEL_LENGTH 30
#define MAX_DATA 50

typedef enum Registers {
	r1, r2, r3, r4
} Register;
enum _OperandType {
	Code, Data, String
};

union _OperandData {
	int number;
	char label[LABEL_LENGTH];
	Register reg;
};


enum _SymbolType {
	Data, Code, String
};

typedef union OperandData {
	int number;
	char label[LABEL_LENGTH];
	Register reg;
} OperandData;

typedef enum OperandType {
	Reg, Number, Label
} OperandType;


typedef struct _Operand {
	OperandData data;
	OperandType type;
} Operand;

typedef enum _SymbolType SymbolType;
typedef struct Symbol {
	char label[LABEL_LENGTH];
	int counter;
	int content[MAX_DATA];
	int size;
	enum SymbolType type;
	struct Symbol *next;

} Symbol;

typedef struct Instruction {
	Operand operands[2];
	int numOperands;
	int L;
	int instructionId;
	struct Instruction *next;

} Instruction;

Symbol *lookup(Symbol *, char *);

#endif

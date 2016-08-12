#pragma once

#ifndef datastructures_h 
#define datastructures_h

#define LABEL_LENGTH 30
#define MAX_DATA 80

typedef enum Registers {
	r1, r2, r3, r4
} Register;




typedef enum SymbolType {
	Data, Code, String
} SymbolType;

typedef union OperandData {
	int number;
	char label[LABEL_LENGTH];
	Register reg;
} OperandData;

typedef enum OperandType {
	Reg, Number, Label
} OperandType;


typedef struct Operand {
	OperandData data;
	OperandType type;
} Operand;

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

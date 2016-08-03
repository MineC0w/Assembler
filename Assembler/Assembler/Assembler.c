#include <stdio.h>
#include <string.h>
#include "datastructures.h"

#define IGNORE_SPACES(n,i) { for(++i; n[i] == ' ' || n[i] == '\t'; ++i); }
#define GET_NUM(num, i, src) { };

#define LINE_LENGTH 80
#define LABEL_LENGTH 30
#define MAX_OP_LENGTH 4

#define TRUE 1
#define FALSE 0

#define DELIMITER 101
#define BLANK_LABEL "$"

/* Prototypes */
int assemble(char *filename);
int isLegalChar(char c);
Operand getOperand(char line[LINE_LENGTH], int);
int getNumber(char *, int *);
/* Global variables */
Symbol *ExternTable = NULL;
Symbol *SymbolTable = NULL;

#pragma warning(disable : 4996)

int main(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; ++i)
	{
		assemble(argv[i]);
	}

	return 0;
}

int assemble(char *filename)
{
	FILE *data = NULL;
	int instructionCounter, dataCounter, lineCounter;
	char lineContent[LINE_LENGTH];

	instructionCounter = dataCounter = 0;
	data = fopen(filename, "r");

	/* Go over all lines */
	for (lineCounter = 1; fgets(lineContent, LINE_LENGTH, data); lineCounter++)
	{
		/* Go over each row individually */

		char label[LABEL_LENGTH];
		int currentChar, isLabel, isError;
		isError = isLabel = FALSE;
		/* First check if there is a label */
		for (currentChar = 0; currentChar != ':' && currentChar < LABEL_LENGTH; currentChar++)
		{
			/* Check if the character is allowed to be part of label */
			if (isLegalChar(lineContent[currentChar]))
			{
				label[currentChar] = lineContent[currentChar];
			}
			else {
				isError = TRUE;
				break;
			}
		}
		/* Check if loop terminated because it found a proper label. Would otherwise terminate before */
		if (lineContent[currentChar] == ':')
			isLabel = TRUE;

		/* Reset the current character if needed */
		currentChar = isLabel ? currentChar : 0;

		/* Right now label[] contains the label, if there is one. Need to check if it's a special instruction or an operator. */
		IGNORE_SPACES(lineContent, currentChar);

		/* Now there has to be either a dot ('.') or the beginning of an operator */
		if (lineContent[currentChar] == '.')
		{
			/* It is a special instruction */
			char specialInstruction[10];
			int i;

			for (i = 0, currentChar++; lineContent[currentChar] != ' '; i++, currentChar++) {
				specialInstruction[i] = lineContent[currentChar];
			}
			IGNORE_SPACES(lineContent, currentChar);
			if (strcmp("data", specialInstruction)) {
				/* .data instruction, get the numbers */
				int size = 0;
				int numbers[MAX_DATA];
				/* Get all numbers in the line */
				while (lineContent[currentChar] != '\n')
				{
					int n;

					n = getNumber(lineContent, &currentChar);
					if(lineContent[currentChar] != ',') { /* error */}
					numbers[size] = n;
					IGNORE_SPACES(lineContent, currentChar);

					size++;
				}

				/* Insert the data instruction to the table */

				Symbol sym;
				sym.counter = dataCounter;
				sym.size = size;
				/* If there is a label, attach it, otherwise attach a blank label "$" */
				if (isLabel)
					strcpy(sym.label, label);
				else
					strcpy(sym.label, BLANK_LABEL);
				sym.type = Data;
				for (i = 0; i < size; i++)
				{
					sym.content[i] = numbers[i];
				}

				/* Actually insert it */
				if (SymbolTable == NULL)
				{
					/* First time */

					SymbolTable = &sym;
					
				}
				else {
					if (lookup(SymbolTable, label) != NULL && isLabel) {
						/* Error: Can't have same labels twice */
					} else
						SymbolTable->next = &sym;
				}

				dataCounter += size;

			}
			else if (strcmp("string", specialInstruction)) {
				/* .string instruction */
			}
			else if (strcmp("extern", specialInstruction)) {
				/* .extern instruction */
			}
			else if (strcmp("entry", specialInstruction)) {
				/* .entry instruction */
			}
			else {
				/* unknown instruction */

			}
			
			
		}
		else
		{
			/* An instruction.  */
			short numOperands = 0;
			Operand operands[2];

			/* Get the operator */
			char op[MAX_OP_LENGTH] = { lineContent[currentChar],lineContent[currentChar + 1],lineContent[currentChar + 2],lineContent[currentChar + 3] };

			currentChar += lineContent[lineCounter] == ' ' ? 3 : 4;
			IGNORE_SPACES(lineContent, lineCounter);
			
			/* Now all that's remaining is either 1, 2, or no operands. */
			if (lineContent[lineCounter] == '\n')
			{
				/* No operands. */
			}
			else {
				numOperands++;
				/* One or two operands, get them. */

				operands[0] = getOperand(lineContent, lineCounter);

				/* Check if there's a second operand */

				IGNORE_SPACES(lineContent, lineCounter);

				if (lineContent[lineCounter] == ',') {
					numOperands++;
					getOperand(lineContent, lineCounter);

				}
				else if (lineContent[lineCounter] == '\n') {
					/* only one operand */
				}
				else {
					/* illegal char */
				}

				IGNORE_SPACES(lineContent,lineCounter);

				if (lineContent[lineCounter] != '\n') 
				{
					/* Error: can't have more characters after the 2nd operand */
				}
				else {
					/* Everything is all right. Calculate L and update the label, if it exists. */
					int L = 1;
					if (numOperands == 1) { L = 2; }
					if (numOperands == 2) {
						/* Complicated. Need to check more precisely operands. */

						if (operands[0].type == Reg && operands[1].type == Reg);
						if (operands[0].type == Label) L++;
					}

					/* Finally ready to finish with processing the line. */

					

					instructionCounter += L;
				}


			}


		}

	}
	
	fclose(data);
	/* Finished going over all lines first time, ready to create machine code */
	


}

int isLegalChar(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}

Operand getOperand(char line[LINE_LENGTH], int i) {
	Operand op;

	/* Check if number */
	if (line[i] == '#')
	{
		
		int num;
		num = getNumber(line, &i);

		op.type = Number;
		op.data.number = num;
		
	}
	else if (line[i] == 'r' && !isLegalChar(line[i + 2]) && line[i + 1] > '0' && line[i + 1] < '7') {
		/* Register */
		op.type = Reg;
		switch (line[i + 1])
		{
		case 1: op.data.reg = r1; break;
		case 2: op.data.reg = r2; break;
		case 3: op.data.reg = r3; break;
		case 4: op.data.reg = r4; break;
		default: /* ERROR: Unknown register */ break;

		}
	}
	else {
		/* Label */
		char label[LABEL_LENGTH];
		int j;
		for (j = i; j < LABEL_LENGTH && isLegalChar(line[j]); j++)
		{
			/* j = i + <current_iteration_number> */
			label[j - i] = line[j];
		}

		if (line[j] == '[') {
			/* Special label stuff */

		}
	}

	return op;
}

int getNumber(char line[LINE_LENGTH], int *i)
{
	int num = (line[*i + 1] == '+') ? 1 : -1;
	if (line[*i + 1] != '-' && num == -1) { /* Illegal num */ }
	/* get the number */
	for (*i++; line[*i] != ' ' && line[*i] != ','; *i++)
	{
		num *= 10;
		num += line[*i] - '0';
	}

	return num;
}
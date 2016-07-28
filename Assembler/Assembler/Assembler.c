#include <stdio.h>
#include <string.h>
#include "datastructures.c"

#define IGNORE_SPACES(n,i) { for(++i; n[i] == ' ' || n[i] == '\t'; ++i); }

#define LINE_LENGTH 80
#define LABEL_LENGTH 30
#define MAX_OP_LENGTH 4

#define TRUE 1
#define FALSE 0

/* Prototypes */
int assemble(char *filename);
int isLegalChar(char c);
/* Global variables */
Symbol ExternTable;

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
	FILE *data;
	int instructionCounter, dataCounter, lineCounter;
	char lineContent[LINE_LENGTH];

	fopen(filename, "r");

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
		}
		else
		{
			/* An instruction.  */
			short numOperands = 0;
			operand operands[2];

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
					}

					/* Finally ready to finish with processing the line. */
				}


			}


		}

	}

}

int isLegalChar(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}

operand getOperand(char line[LINE_LENGTH], int i) {
	/* Check if number */
	if (line[i] == '#')
	{
		int num = (line[i+1] == '+') ? 1 : -1;
		if(line[i+1] != '-' && num == -1) { /* Illegal num */}
		/* Number */
		for (i++; line[i] != ' ' && line[i] != ','; i++)
		{
			i *= 10;
			i += line[i] - '0';
		}
	}
	else if (line[i] == 'r' && !isLegalChar(line[i + 2]) && line[i + 1] > '0' && line[i + 1] < '7') {
		/* Register */
	}
	else {
		/* Label */
	}
}
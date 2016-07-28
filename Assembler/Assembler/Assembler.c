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
				/* One or two operands, get them. */


			}


		}

	}

}

int isLegalChar(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}
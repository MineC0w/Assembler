#include "datastructures.h"

#define MOV
#define STOP

#define WORD_SIZE 15
int operatorToInt(Operand op)
{

}


char *instructionToBinary(Instruction inst)
{
	/* Converts a raw instruction to the required binary */

	char *instructionBinaryData;

	instructionBinaryData = malloc(sizeof(char) * inst.L * WORD_SIZE);

	switch (inst.instructionId)
	{
		/* Sets bits 3-5 to the required opcode */
	}
}
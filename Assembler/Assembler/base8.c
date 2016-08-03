#include <math.h>

/* Converts an array of binary digits to an array of base 8 digits*/
char *convertToBase8(char *data, int length)
{
	char *converted;
	int counter; 
	/* Assign an array of length log(length) - the length of the data in base 8, plus one more slot to terminate the string */
	converted = malloc(((int)(length/3) + 1) * sizeof(char));

	/* Set the final character so that it's a proper string */
	converted[(int)(length / 3) + 1] = '\0';

	for (counter = length; counter >= 3; counter -= 3)
	{
		/* Convert 3 binary digits to 1 octal digit */

		
	}

	return converted;
}
#ifndef LABEL_LENGTH
#define LABEL_LENGTH 30
#endif

#ifndef NULL
#define NULL 0
#endif

#include "datastructures.h"

/* Define at most 80 numbers or string characters to be used in a single .data line, line length is at most 80 anyway */
#define MAX_DATA 80






/* Finds a symbol with the given label */
Symbol *lookup(Symbol *table, char *name)
{
	while (table->next != NULL)
	{
		if (strcmp(name, table->label)) {
			/* Found it */
			return table;
		}

		table = table->next;
	}

	return NULL;
}
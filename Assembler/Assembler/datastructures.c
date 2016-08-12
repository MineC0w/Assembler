#ifndef LABEL_LENGTH
#define LABEL_LENGTH 30
#endif

#ifndef NULL
#define NULL 0
#endif

#include "datastructures.h"
#include <string.h>



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
/*
 * August 5th, 2023
 *
 * hash_table.h
 *
 * Alex McColm
 *
 * Implementation of the header file `hash_table.h`.
 */
#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

// DJB hash function by Dan Bernstein of the usergroup "comp.lang.c".
unsigned int djb_hash(char * s)
{
    unsigned long hash = 5381;
    int c;

    while (c = *s++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

struct hash_table *hashtable_create()
{
	struct hash_table *new_ht = calloc(1, 
		sizeof(struct hash_table) + INITIAL_SIZE * sizeof(char *));

	new_ht->strings = calloc(INITIAL_SIZE, sizeof(char *));
	new_ht->array_size = INITIAL_SIZE;
	new_ht->array_elems = 0;
	new_ht->hash = djb_hash;
}

int hashtable_insert(struct hash_table *ht, char * s)
{
	unsigned int s_index = (* ht->hash)(s) % ht->array_size;
	unsigned int probes = 0;

	while (ht->strings[s_index] != NULL)
	{
		s_index = (s_index + 1) % ht->array_size;
		probes++;
		if (probes == MAX_PROBES)
		{
			printf("Failed to add %s!\n", s);
			return -1;
		}
	}

	ht->strings[s_index] = s;
	return 0;
}

int hashtable_remove(struct hash_table *ht, char * s)
{
	// Get the hash of the search key
	unsigned int s_index = (* ht->hash)(s) % ht->array_size;
	
	// Limit on linear probing
	unsigned int probes = 0;

	// Empty string index would indicate empty-since-start, terminating search
	while (ht->strings[s_index] != NULL)
	{
		if (strcmp(ht->strings[s_index], s) == 0)
		{
			free(s);
			ht->strings[s_index] = NULL;
			return 1;
		}

		s_index = (s_index + 1) % ht->array_size;
		probes++;
		if (probes == MAX_PROBES)
		{
			break;
		}
	}

}

int hashtable_contains(struct hash_table *ht, char * search_key)
{
	// Get the hash of the search key
	unsigned int s_index = (* ht->hash)(search_key) % ht->array_size;
	
	// Limit on linear probing
	unsigned int probes = 0;

	// Empty string index would indicate empty-since-start, terminating search
	while (ht->strings[s_index] != NULL)
	{
		if (strcmp(ht->strings[s_index], search_key) == 0)
		{
			return 1;
		}

		s_index = (s_index + 1) % ht->array_size;
		probes++;
		if (probes == MAX_PROBES)
		{
			break;
		}
	}

	return 0;
}

struct hash_table * hashtable_resize(struct hash_table *ht, size_t size)
{
	struct hash_table *new_ht = realloc(ht, sizeof(struct hash_table) + sizeof(char *) * size);
	if (new_ht == NULL)
		return NULL;
	ht = new_ht;
	ht->strings = realloc(ht->strings, sizeof(char *) * size);
	ht->array_size = size;
	return ht;
}

void hashtable_print_contents(struct hash_table *ht, FILE *fp)
{
	unsigned int i = 0;

	fprintf(fp, "[Index]: Content;\n");

	for (i; i < ht->array_size; i++)
	{
		if ( (i % 2 == 0))
		{
			fputc('\n', fp);
		}
		fprintf(fp, "[%d]: \"%s\";\t\t", i, ht->strings[i]);
	}
	fputc('\n', fp);

}
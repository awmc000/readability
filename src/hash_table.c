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
#include <assert.h>
#include <regex.h>

/**
 * @brief Generates a hash code for a string. Algorithm by Dan 
 * Bernstein of usergroup comp.lang.c
 * @param s Any string
 * @return Hash code given as an unsigned int
 **/
unsigned int djb_hash(char * s)
{
    unsigned long hash = 5381;
    int c;

    while (c = *s++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

/**
 * @brief Constructs a hash table on the heap with the specified
 * initial size.
 * @param initial_size Initial size in elements
 * @return Pointer to new hash table.
 **/
struct hash_table *hashtable_create(size_t initial_size)
{
	struct hash_table *new_ht = calloc(1, 
		sizeof(struct hash_table) + initial_size * sizeof(char *));

	new_ht->strings = calloc(initial_size, sizeof(char *));
	new_ht->array_size = initial_size;
	new_ht->array_elems = 0;
	new_ht->hash = djb_hash;
}

/**
 * @brief Inserts a string into a hash table. Uses linear probing,
 * failing to insert if MAX_PROBES attempted and failed.
 * @param ht Pointer to a hash table
 * @param s Any string
 * @return 1 for success, 0 for failure.
 **/
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
			return 0;
		}
	}

	ht->strings[s_index] = s;
	ht->array_elems++;
	return 1;
}

/**
 * @brief Searches for an element in a hash table and if found
 * removes the first matching element.
 * @param ht Pointer to the hash table
 * @param s Search key
 * @return 1 for success or 0 for failure.
 **/
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
			ht->array_elems--;
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

/**
 * @brief Returns whether or not a hash table contains the search 
 * key.
 * @param ht Pointer to the hash table
 * @param search_key String to find a match for
 * @return 1 if contained or 0 if not contained or operation failed
 **/
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

/**
 * @brief Adjusts the size of a hash table.
 * @param ht Pointer to the hash table
 * @param size New size in elements
 * @return Pointer to the new, resized hash table
 **/
struct hash_table * hashtable_resize(struct hash_table *ht, size_t size)
{
	struct hash_table *new_ht = realloc(ht, sizeof(struct hash_table) + sizeof(char *) * size);
	
	if (new_ht == NULL)
	{
		return ht;
	
	}
	
	ht = new_ht;
	ht->strings = realloc(ht->strings, sizeof(char *) * size);
	ht->array_size = size;
	
	return ht;
}

// TODO: break up this very long function
/**
 * @brief Loads a pre-determined number of words from a file
 * into the specified hash table.
 * @param ht Pointer to the hash table
 * @param fp Pointer to a text file
 * @param num_words Number of words to load
 * @return 1 for success
 **/
int hashtable_load_words_from_file(struct hash_table *ht, FILE * fp, size_t num_words)
{
	if (fp == NULL)
	{
		printf("Cannot load a null file pointer!\n");
		return 0;
	}

	// Set up buffer for file
	char * buf_line = calloc(256, sizeof(char));
	size_t buf_size = 0;

	// Set up string array for words parsed from file
	char ** word_array = calloc(num_words, sizeof(char *));

	if (word_array == NULL)
	{
		printf("Failed to allocate word_array for %lu words!", num_words);
		free(buf_line);
		free(word_array);
		return 0;
	}

	

	// set up word regex pattern
	regex_t word_re;

	int word_comp = regcomp(&word_re, "[0-9A-Za-z']+", REG_EXTENDED);
	
	assert(word_comp == 0);

	int words = 0;

	while ( getline(&buf_line, &buf_size, fp) != -1 )
	{
		// get words from line
		regmatch_t matches[1];

		word_comp = regexec(&word_re, buf_line,
							sizeof(matches) / sizeof(matches[0]),
							(regmatch_t *) &matches, 0);
		
		// allocate string
		char *this_word = calloc(matches[0].rm_eo - matches[0].rm_so + 1, sizeof(char));
		
		for (unsigned int i = matches[0].rm_so; i < matches[0].rm_eo; i++)
		{
			this_word[i - matches[0].rm_so] = buf_line[i];
		}

		this_word[matches[0].rm_eo - matches[0].rm_so] = '\0';
		
		// put in word array
		word_array[words] = this_word;
		words++;
	}

	for (int i = 0; i < words; i++)
	{
		hashtable_insert(ht, word_array[i]);
	}

	// Free the memory used by the regular expression
	regfree(&word_re);

	// Free the line buffer
	free(buf_line);

	// Free the array
	free(word_array);

	return 1;
}

int hashtable_load_lines_from_file(struct hash_table *ht, FILE * fp, size_t num_lines)
{
	// TODO: implement
}

/**
 * @brief Prints the contents of a hash table to a specified
 * file, eg. a text file, stdout, or stderr.
 * @param ht Pointer to the hash table
 * @param fp Pointer to the file
 **/
void hashtable_print_contents(struct hash_table *ht, FILE *fp)
{
	unsigned int i = 0;
	unsigned elems_printed = 0;

	fprintf(fp, "[Index]: Content;\n");

	for (i; i < ht->array_size; i++)
	{
		
		if (ht->strings[i] != NULL)
		{
			fprintf(fp, "[%d]: \"%s\";\t\t", i, ht->strings[i]);
			elems_printed++;
			if ( (elems_printed % 2 == 0))
			{
				fputc('\n', fp);
			}
		}
	}
	fputc('\n', fp);
}

/**
 * @brief Frees every element of a hash table, to prepare for
 * deletion of the hash table struct itself.
 * @param ht Pointer to the hash table.
 **/
void hashtable_delete(struct hash_table *ht)
{
	for (unsigned int i = 0; i < ht->array_size; i++)
	{
		if (ht->strings[i] != NULL)
		{
			free(ht->strings[i]);
			ht->array_elems--;
		}
	}
	free(ht->strings);
}
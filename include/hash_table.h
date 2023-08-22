/*
 * August 5th, 2023
 *
 * hash_table.h
 *
 * Alex McColm
 *
 * Hash table for quick access to strings for comparison.
 **/
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>

#define INITIAL_SIZE 800
#define MAX_PROBES 100

struct hash_table {
	unsigned int array_size;
	unsigned int array_elems;
	unsigned int (*hash)(char *);
	char **strings;
};

/**
 * Returns a pointer to a newly allocated hashtable or NULL if allocation 
 * failed.
 **/
struct hash_table *hashtable_create(size_t initial_size);

/**
 * Inserts the string `s` to the hash table `ht`. Returns 1 on success and 0 
 * for failure.
 **/
int hashtable_insert(struct hash_table *ht, char * s);

/**
 * Removes the string `s` from the hash_table `ht`. Returns 1 if found and 
 * removed and 0 if not found.
 **/
int hashtable_remove(struct hash_table *ht, char * s);

/**
 * Removes the string `s` from the hash_table `ht`. Returns 1 if found and 0
 * if not found.
 **/
int hashtable_contains(struct hash_table *ht, char * search_key);

/**
 * Resize the hash table to the specified size.
 * Uses the C library function `realloc()`.
 **/
struct hash_table *hashtable_resize(struct hash_table *ht, size_t size);

/**
 * Loads all words from the file stream `fp` to EOF. A word is a series of
 * chars containing letters of the alphabet or numbers, and possibly hyphens.
 * Eg. "Hello", "1945", "3rd", "tip-top".  
 **/
int hashtable_load_words_from_file(struct hash_table *ht, FILE * fp, size_t num_words);

/**
 * Loads all lines from the file stream `fp` up to EOF into `ht`.
 * Newlines are not added.
 **/
int hashtable_load_lines_from_file(struct hash_table *ht, FILE * fp, size_t num_lines);


/**
 * Prints the contents of the hash table to the given file pointer.
 **/
void hashtable_print_contents(struct hash_table *ht, FILE *fp);

#endif // HASH_TABLE_H
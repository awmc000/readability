/*
 * August 5th, 2023
 *
 * main.c
 *
 * Alex McColm
 *
 * Main loop of a readability assessment program.
 */
#include <stdio.h>
#include <regex.h>
#include "hash_table.h"

void assess_readability(FILE *text_file)
{
	puts("assess_readability called, but still a stub");

	struct hash_table *easy_words   = hashtable_create();
	
	struct hash_table *prepositions = hashtable_create();
	
	// TODO: Load file of Lorge easy words list into hash table.
	// TODO: Load file of prepositions into hash table.

	// TODO: Begin analysis using Lorge method.
}

int main(int argc, char *argv[])
{
	// If filename given, use that
	if (argc == 2)
	{
		FILE *f = fopen(argv[1], "r");
		assess_readability(f);
		return 0;
	}

	// Else, take input line by line until sentinel value.
	else if (argc == 1)
	{
		assess_readability(stdin);
		return 0;
	}
	else
	{
		puts("Invalid arguments given: either 0 args or 1 filename allowed.");
		return 1;
	}

	return 0;
}
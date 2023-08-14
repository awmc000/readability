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
#include <assert.h>
#include <stdlib.h>
#include "hash_table.h"
#include "io.h"

void handle_load(int load_success, const char *desc)
{
	switch (load_success)
	{
	case 1:
		printf("%s loaded successfully.\n", desc);
		break;
	case 0:
		printf("%s failed to load.\n", desc);
		break;
	default:
		printf("unknown load success code received!\n");
	}
}

void assess_readability(FILE *text_file)
{
	struct hash_table *easy_words   = hashtable_create(3000);
	
	struct hash_table *prepositions = hashtable_create(300);

	int load_success;

	// Load file of Lorge easy words list into hash table.
	FILE * fp_easy_words = fopen("dale list of 769 easy words", "r");
	load_success = hashtable_load_words_from_file(easy_words, fp_easy_words, 1500);
	handle_load(load_success, "dale list of 769 easy words");

	hashtable_print_contents(easy_words, stdout);

	// Load file of prepositions into hash table.
	FILE * fp_prepositions = fopen("prepositions", "r");
	load_success = hashtable_load_words_from_file(prepositions, fp_prepositions, 300);

	handle_load(load_success, "List of prepositions");

	hashtable_print_contents(prepositions, stdout);

	// Track the number of sentences by counting their ending punctuation.
	// Compute the average length of a sentence in words.
	// Track the number of words which are not on the easy word list.
	// Track the number of prepositions.

	// Set up the buffer for text reading.
	char * buf_line = calloc(256, sizeof(char));
	size_t buf_size;

	
	int sentences = 0;
	int words = 0;

	
	// Count sentences and words.
	while ( getline(&buf_line, &buf_size, text_file) != -1 )
	{
		puts(buf_line);
		sentences += count_sentences(buf_line);
		words += count_words(buf_line);
	}

	printf("%d words and %d sentences.\n", words, sentences);

	// Roll back the tape for word analysis stage.
	rewind(text_file);

	size_t num_words = words;
	char ** word_arr = calloc(2 * num_words, sizeof(char *));
	size_t *word_arr_elems;

	int array_creation_success = words_array(text_file, num_words, word_arr);

	int easy_words_count = 0;
	int prepositions_count = 0;

	for (unsigned int i = 0; i < words; i++)
	{
		printf("[%d]: \"%s\"\n", i, word_arr[i]);
		if (hashtable_contains(easy_words, word_arr[i]))
		{
			printf("%s is an easy word.\n", word_arr[i]);
			easy_words_count++;
		}

		if (hashtable_contains(prepositions, word_arr[i]))
		{
			printf("%s is a preposition.\n", word_arr[i]);
			prepositions_count++;
		}
	}
	printf("%d easy words of %d words and %d prepositions in %d sentences.\n", 
		easy_words_count, words, prepositions_count, sentences);
	printf("%f average words per sentence.\n", (float) words / sentences);
}

int main(int argc, char *argv[])
{
	// If filename given, use that
	if (argc == 2)
	{
		printf("%s\n", argv[1]);
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
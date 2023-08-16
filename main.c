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

void print_score_bracket(double dale_chall_score)
{
	printf("Easily understood by an average student in ");
	
	if (dale_chall_score <= 4.9)
	{
		printf("4th grade or lower\n");
		return;
	}

	if (dale_chall_score <= 5.9)
	{
		printf("5th or 6th grade\n");
		return;
	}

	if (dale_chall_score <= 6.9)
	{
		printf("7th or 8th grade\n");
		return;
	}

	if (dale_chall_score <= 7.9)
	{
		printf("9th or 10th grade\n");
		return;
	}

	if (dale_chall_score <= 8.9)
	{
		printf("11th or 12th grade\n");
		return;
	}

	if (dale_chall_score <= 9.9)
	{
		printf("college\n");
		return;
	}

	printf("college graduate\n");
}

void assess_readability(FILE *text_file)
{
	struct hash_table *easy_words   = hashtable_create(6000);

	// Load file of Lorge easy words list into hash table.
	FILE * fp_easy_words = fopen("lists/dale3000", "r");
	int load_success = hashtable_load_words_from_file(easy_words, 
		fp_easy_words, 1500);
	
	handle_load(load_success, "dale3000");

	// Set up the buffer for text reading.
	char * buf_line = calloc(256, sizeof(char));
	size_t buf_size;

	int total_sentences = 0, sentences = 0;
	int total_words = 0, words = 0;

	int easy_words_count = 0;

	// Count sentences and words.
	while ( getline(&buf_line, &buf_size, text_file) != -1 )
	{
		// count sentences and words in the line
		sentences = count_sentences(buf_line);
		words = count_words(buf_line);
		
		// add to text totals
		total_sentences += sentences;
		total_words += words;

		// put words in a special array
		size_t num_words = words;
		char ** word_arr = calloc(2 * words, sizeof(char *));
		size_t *word_arr_elems;

		int array_creation_success = words_array_from_string(buf_line, 
			num_words, word_arr);

		// Check if each word is an easy word
		for (unsigned int i = 0; i < words; i++)
		{
			if (hashtable_contains(easy_words, word_arr[i]))
			{
				easy_words_count++;
			}
		}
	}

	int difficult_words = total_words - easy_words_count;

	double diff_pct = (double) difficult_words / (double) total_words * 100.0;
	double words_per_sent = total_words / total_sentences;

	double score = 0.1579 * diff_pct +  (0.0496 * words_per_sent); 

	if (diff_pct > 5.0)
		score += 3.6365;

	printf("Dale-Chall score of %f\n", score);
	print_score_bracket(score);
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
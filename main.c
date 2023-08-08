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

	// Compile regular expression(s).
	const char * sentence_pattern = "[.;?!]+"; //"\\b((?!=|\\.).)+.\\b";
	const char * word_pattern = "[A-Z]{0,1}[a-z0-9]+";

	regex_t sentence_re;
	regex_t word_re;

	int sent_exp_comp = regcomp(&sentence_re, sentence_pattern, REG_EXTENDED);
	int word_exp_comp = regcomp(&word_re, word_pattern, REG_EXTENDED);

	assert(sent_exp_comp == 0);
	assert(word_exp_comp == 0);

	// Track the number of sentences by counting their ending punctuation.
	// Compute the average length of a sentence in words.
	// Track the number of words which are not on the easy word list.
	// Track the number of prepositions.

	// Set up the buffer for text reading.
	char * buf_line = calloc(256, sizeof(char));
	size_t buf_size;

	
	while ( getline(&buf_line, &buf_size, text_file) != -1 )
	{
		puts(buf_line);
		// Get sentence ends on this line.
		regmatch_t sentence_end_match;


		// Count of matches
	    size_t match_count = 0;

	    // Perform the match
	    regmatch_t match;
	    int input_offset = 0;
	    while (regexec(&sentence_re, buf_line + input_offset, 1, &sentence_end_match, 0) == 0) {
	        match_count++;
	        input_offset += match.rm_eo;  // Move to the end of the matched substring
	    }

		printf("%lu sentences\n", match_count);
	}

	regfree(&sentence_re);
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
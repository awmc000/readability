/*
 * io.c
 *
 * August 7th, 2023
 *
 * Alex McColm
 *
 * Implementation of functions for counting words and sentences and
 * storing words in arrays.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "util.h"


int count_words(char * s)
{
	bool started = false;
	int count = 0;

	for (unsigned int i = 0; i < strlen(s); i++)
	{
		if (isalpha(s[i]) || isdigit(s[i]) || s[i] == '\'')
		{
			if (!started)
			{
				started = true;
			}
		}
		else
		{
			if (started)
			{
				started = false;
				count++;
			}
		}
	}

	return count;
}

int count_sentences(char * s)
{
	bool started = false;
	int count = 0;

	for (unsigned int i = 0; i < strlen(s); i++)
	{
		char c = s[i];
		if (c == '.' || c == '?' || c == '!' || c == ';')
		{
			if (i == strlen(s) - 1)
			{
				count++;
				break;
			}
			if (!started)
			{
				started = true;
			}
		}
		else
		{
			if (started)
			{
				started = false;
				count++;
			}
		}
	}

	return count;
}


void extract_words(char * str, int ** array_size, char ** allocate_at)
{
	// Count the number of words in the array.
	int words = count_words(str);

	// Allocate space for words个 strings at given address.
	allocate_at = calloc(words, sizeof(char *));

	// Set array size.
	**array_size = words;

	// Iterate over string inserting words to the array.
	int words_inserted = 0;
	
	int position = 0;

	while (words_inserted < words)
	{
		// pass any non alpha chars
		while (!isalpha( * (str + position) ))
			position++;		

		// run extract_word on str + position
		char * next_word = extract_word(str + position);

		// move past the current word
		str += strlen(next_word);

		words_inserted++;
	}
}

int words_array_from_string(char * s, size_t num_words, char ** s_array)
{
	// TODO: eliminate use of Regex, just iterate and use ctype
	// set up word regex pattern
	regex_t word_re;

	int words_counted = 0;

	int word_comp = regcomp(&word_re, "[0-9A-Za-z]+", REG_EXTENDED);
	
	assert(word_comp == 0);
		
	// get words from line one at a time
	regmatch_t matches[1];
	int offset = 0;

	while ( (word_comp = regexec(&word_re, s + offset,
						sizeof(matches) / sizeof(matches[0]),
						(regmatch_t *) &matches, 0)) == 0)
	{
		// allocate string
		char *this_word = calloc(matches[0].rm_eo - matches[0].rm_so + 1, sizeof(char));
		
		// record its length
		int this_word_len = 0;

		// copy each char over to `this_word`
		for (unsigned int i = matches[0].rm_so; i < matches[0].rm_eo; i++)
		{
			this_word[this_word_len] = tolower(s[i]);
			this_word_len++;
		}
		this_word[this_word_len] = '\0';
			
		// put in word array
		s_array[words_counted] = this_word;
		words_counted++;
		s += matches[0].rm_eo + 1;
	}

	regfree(&word_re);

	return 1;
}
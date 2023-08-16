#ifndef IO_H
#define IO_H

#include <stddef.h>
#include <stdio.h>

/*
 * Counts words in `s` in a simple way: contiguous chars that are alphabetic,
 * digits, hyphens or apostrophes.
 */
int count_words(char * s);

/*
 * Counts sentences in `s` by counting contiguous sequences of one or more 
 * punctuation mark: '.', '?', '!', or ';'.
 */
int count_sentences(char * s);

/*
 * Given a string `s`, the number of words in it `num_words`, and a string 
 * array `s_array`, stores words in the array.
 */
int words_array_from_string(char * s, size_t num_words, char ** s_array);

#endif // IO_H
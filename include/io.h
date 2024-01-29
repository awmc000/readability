/*
 * io.h
 *
 * August 7th, 2023
 *
 * Alex McColm
 *
 * Functions for counting words and sentences and
 * storing words in arrays.
 */
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

/*
 * Given a string and memory locations for the array size and array itself,
 * stores the words in the array, determining how many there are and placing
 * that quantity in the array_size variable.
 */
void extract_words(char * str, int ** array_size, char ** allocate_at);


#endif // IO_H
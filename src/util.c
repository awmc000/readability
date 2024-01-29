#include <ctype.h>
#include <stdlib.h>

char * extract_word(char *buf_line)
{
	char * this_word;
		
	// Count number of chars before newline
	int chars = 0;
		
	for (char * c = buf_line; isalpha(*c); ++c)
		chars++;

	// Allocate this_word with that many plus null byte
	this_word = calloc(chars + 1, sizeof(char));

	// Copy over
	for (int i = 0; i < chars; i++)
		this_word[i] = buf_line[i];

	// Add null byte
	this_word[chars] = '\0';

	return this_word;
}
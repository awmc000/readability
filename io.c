#include "io.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int count_words(char * s)
{
	bool started = false;
	int count = 0;

	for (unsigned int i = 0; i < strlen(s); i++)
	{
		if (isalpha(s[i]))
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
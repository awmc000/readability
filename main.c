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
#include "scoring.h"

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
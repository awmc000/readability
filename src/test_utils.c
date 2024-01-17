#include "test_utils.h"
#include <time.h>
#include <stdio.h>

typedef long nanosecond;

void announce_test(int count, char * name, int test(void))
{
	
	struct timespec res;
	nanosecond before, after;

	printf("\n\n\n========== TEST %d, %s ==========\n\n\n", count, name);

	// Get the start time
	clock_gettime(CLOCK_REALTIME, &res);
	before = res.tv_nsec;

	// Run the test and store pass/fail status
	int result = (*test)();

	// Get the completion time
	clock_gettime(CLOCK_REALTIME, &res);
	after = res.tv_nsec;

	// Take the difference and divide by one million for milliseconds
	nanosecond diff = after - before;

	if (result == 1)
	{
		printf(ANSI_COLOR_GREEN);
		printf("PASSED IN %lu NS \n", diff);
		printf(ANSI_COLOR_RESET);
	}
	else
	{
		printf(ANSI_COLOR_RED);
		printf("\aFAILED!\n");
		printf(ANSI_COLOR_RESET);
	}
}
#include "scoring.h"
#include "test_utils.h"
#include <stdio.h>

/*
void print_score_bracket(double dale_chall_score);
double assess_readability(FILE *text_file);
*/

// Test case forward declarations

/*
 4th grade
5th or 6th grade
7th or 8th grade
9th or 10th grade
11th or 12th grade
college
college graduate
*/

int assess_roysullivan3();
int assess_electoralcollege3();
int assess_modelt4();
int assess_raisedbydogs4();
int assess_alchemy5();
int assess_nomads6();

int strip_plural_markers();
int strip_past_tense();
// Main method runs test cases printing results with announce_test
int main(void)
{
	int test_num = 0;

	// announce_test(test_num, "Creating a HT", &can_create); 
	RUN_TEST(assess_roysullivan3)

	RUN_TEST(assess_electoralcollege3)

	RUN_TEST(strip_plural_markers)

	RUN_TEST(strip_past_tense)
	return 0;
}


// Test case function definitions
int assess_roysullivan3()
{
	// double assess_readability(FILE *text_file);
	FILE *fp = fopen("testdata/roysullivan3", "r");

	double score = assess_readability(fp);
	fclose(fp);
	return (score <= 4.9);
}

int assess_electoralcollege3()
{
	// double assess_readability(FILE *text_file);
	FILE *fp = fopen("testdata/electoralcollege3", "r");

	double score = assess_readability(fp);
	fclose(fp);
	return (score <= 4.9);
}

int assess_modelt4()
{
	// TODO: IMPLEMENT
	return 1;
}

int assess_raisedbydogs4()
{
	// TODO: IMPLEMENT
	return 1;
}

int assess_alchemy5()
{
	// TODO: IMPLEMENT
	return 1;
}

int assess_nomads6()
{
	// TODO: IMPLEMENT
	return 1;
}

int strip_plural_markers()
{
	int all_correct = 1;
	char plurals[][6] = {"roots", "docks", "bones"};
	char singles[][5] = {"root", "dock", "bone"};
	
	for (int i = 0; i < 3; i++)
	{

		if ( strcmp(drop_end_if_s(plurals[i]), singles[i]) != 0 )
			all_correct = 0;
		else
			printf("converted %s to %s\n", plurals[i], singles[i]);
	}

	return all_correct;
}

int strip_past_tense()
{
	int all_correct = 1;
	char plurals[][7] = {"rooted", "docked", "picked"};
	char singles[][5] = {"root", "dock", "pick"};
	
	for (int i = 0; i < 3; i++)
	{

		if ( strcmp(drop_end_if_s(plurals[i]), singles[i]) != 0 )
			all_correct = 0;
		else
			printf("converted %s to %s\n", plurals[i], singles[i]);
	}

	return all_correct;
}
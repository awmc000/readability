#include "scoring.h"
#include "test_utils.h"
#include <stdio.h>

// Test case forward declarations

/*
 *	4.9 or lower 		4th-grade student or lower
 *	5.0–5.9 			5th- or 6th-grade student
 *	6.0–6.9 			7th- or 8th-grade student
 *	7.0–7.9 			9th- or 10th-grade student
 *	8.0–8.9 			11th- or 12th-grade student
 *	9.0–9.9 			college student 
*/

int assess_roysullivan3();
int assess_electoralcollege3();
int assess_modelt4();
int assess_raisedbydogs4();
int assess_alchemy5();
int assess_nomads6();

// Main method runs test cases printing results with announce_test
int main(void)
{
	int test_num = 0;

	RUN_TEST(assess_roysullivan3)

	RUN_TEST(assess_electoralcollege3)

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
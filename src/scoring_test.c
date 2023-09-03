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
int assess_scientist();
int assess_gettysburg();

// Main method runs test cases printing results with announce_test
int main(void)
{
	int test_num = 0;

	RUN_TEST(assess_roysullivan3);

	RUN_TEST(assess_electoralcollege3);

	RUN_TEST(assess_modelt4);

	RUN_TEST(assess_raisedbydogs4);

	RUN_TEST(assess_alchemy5);

	RUN_TEST(assess_scientist);

	RUN_TEST(assess_gettysburg);

	return 0;
}

int test_file_score(const char * filename, double max_acceptable_score)
{
	FILE *fp = fopen(filename, "r");

	double score = assess_readability(fp);
	fclose(fp);
	return (score <= max_acceptable_score);
}

// Test case function definitions
int assess_roysullivan3()
{
	return test_file_score("testdata/roysullivan3", 5.9);
}

int assess_electoralcollege3()
{
	return test_file_score("testdata/electoralcollege3", 7.9);
}

int assess_modelt4()
{
	return test_file_score("testdata/modelt4", 6.9);
}

int assess_raisedbydogs4()
{
	return test_file_score("testdata/raisedbydogs4", 6.9);
}

int assess_alchemy5()
{
	return test_file_score("testdata/alchemy5", 8.9);
}

int assess_nomads6()
{
	return test_file_score("testdata/nomads6", 9.0);
}

int assess_scientist()
{
	return test_file_score("testdata/scientist", 8.0);
}

int assess_gettysburg()
{
	return test_file_score("testdata/gettysburg", 7.5);
}
/*
 * August 7th, 2023
 *
 * io_test.c
 *
 * Alex McColm
 *
 * Tests for the text handling functions.
 */
#include "io.h"
#include "test_utils.h"
#include <assert.h>

// Test case forward declarations
int can_count_zero_words();
int can_count_one_word();
int can_count_50_words_on_line();
int can_count_split_word_as_one();

int can_count_zero_sentences();
int can_count_one_sentence();
int can_count_split_sentences();


int main(void)
{
	int test_num = 0;

	announce_test(test_num, "Count zero words", &can_count_zero_words);
	test_num++;

	announce_test(test_num, "Count one word", &can_count_one_word);
	test_num++;

	announce_test(test_num, "Count 50 words on 1 line", 
		&can_count_50_words_on_line);
	test_num++;

	announce_test(test_num, "Counts a word split on 2 lines as one",
		&can_count_split_word_as_one);
	test_num++;

	announce_test(test_num, "Can count zero sentences",
		&can_count_zero_sentences);
	test_num++;

	announce_test(test_num, "Can count one sentence",
		&can_count_one_sentence);
	test_num++;

	announce_test(test_num, "Can count split sentences",
		can_count_split_sentences);
	test_num++;

	return 0;
}

int can_count_zero_words()
{
	return (count_words("") == 0);
}

int can_count_one_word()
{
	return (count_words("Hello!") == 1);
}

int can_count_50_words_on_line()
{
	char * s = "Lorem ipsum dolor sit amet, consectetur\
	adipiscing elit. Nulla in molestie est. Nulla viverra nisl quis justo \
	dignissim consectetur. Phasellus sollicitudin lacinia ex eget fermentum.\
	Proin ac mi dolor. Nam tellus urna, ultricies et sem eu, scelerisque \
	molestie purus. Praesent dignissim justo et magna vestibulum facilisis.\
	 Quisque malesuada ex mollis.";

	 return (count_words(s) == 50);
}

int can_count_split_word_as_one()
{
	char *s = ", temper-\n-amental!";

	return (count_words(s) == 1);
}

int can_count_zero_sentences()
{
	int result = count_sentences("");
	printf("sentence count of \"%s\" == %d\n", "", result);
	return (result == 0);
}

int can_count_one_sentence()
{
	int result = count_sentences("Hello!");
	printf("sentence count of \"%s\" == %d\n", "Hello!", result);
	return (result == 1);
}


int can_count_split_sentences()
{
	char * s = "Hello,\n World!.!\n Goodbye,\nMars!!";
	int result = count_sentences(s);
	printf("sentence count of \"%s\" == %d\n", s, result);
	return (result == 2);
}

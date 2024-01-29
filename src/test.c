/*
 * test.c
 *
 * January 17th, 2024
 *
 * Unit tests for readability using check
 */
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "io.h"
#include "scoring.h"
#include "trie.h"

START_TEST(test_hashtable_can_create)
{
	struct hash_table *ht = hashtable_create(10);
	hashtable_print_contents(ht, stdout);
}
END_TEST


START_TEST(test_hashtable_can_insert)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
}
END_TEST


START_TEST(test_hashtable_can_find_word)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	ck_assert(hashtable_contains(ht, "Hello"));
}
END_TEST


START_TEST(test_hashtable_can_be_full)
{
		struct hash_table *ht = hashtable_create(100);

	char* words[100] = {
		"apple", "banana", "orange", "grape", "pineapple", "kiwi", "mango", 
		"pear", "watermelon", "strawberry", "peach", "blueberry", "cherry", 
		"apricot", "raspberry", "plum", "lemon", "lime", "coconut", 
		"pomegranate", "avocado", "blackberry", "fig", "guava", "cranberry", 
		"papaya", "melon", "tangerine", "nectarine", "kiwifruit", 
		"passionfruit", "rhubarb", "dragonfruit", "gooseberry", "lychee", 
		"boysenberry", "persimmon", "mulberry", "cantaloupe", "honeydew", 
		"date", "elderberry", "grapefruit", "starfruit", "apricot", "currant", 
		"durian", "jackfruit", "plantain", "kumquat", "tamarind", "cloudberry", 
		"pawpaw", "breadfruit", "quince", "guinep", "ackee", "pummelo", 
		"cupuacu", "salak", "rambutan", "soursop", "santol", "sapote", 
		"surinam cherry", "ugli fruit", "yuzu", "limequat", "lychee", 
		"persimmon", "pomelo", "quincerino", "tamarillo", "ugli fruit", "yuzu", 
		"feijoa", "chirimoya", "black sapote", "canistel", "abiu", "calamondin", 
		"clementine", "blood orange", "white sapote", "breadnut", "jabuticaba", 
		"white currant", "golden kiwi", "green sapote", "redcurrant", 
		"miracle fruit", "green sapote", "honeyberry", "tayberry", "yumberry", 
		"ziziphus", "acai", "safou", "breadnut", "gooseberry"
	};

	unsigned int successful_adds = 0;

	for (int i = 0; i < 100; i++)
	{
		successful_adds += (hashtable_insert(ht, words[i]));
	}

	ck_assert_int_eq(ht->array_elems, 100);
}
END_TEST


START_TEST(test_hashtable_can_remove)
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	hashtable_remove(ht, word);
}
END_TEST


START_TEST(test_hashtable_can_resize)
{
	struct hash_table *ht = hashtable_create(10);

	hashtable_insert(ht, "Hello");
	hashtable_insert(ht, "Bello");
	hashtable_insert(ht, "Mello");
	hashtable_insert(ht, "Yello");
	hashtable_insert(ht, "Sello");

	ht = hashtable_resize(ht, 100);

	ht = hashtable_resize(ht, 200);

}
END_TEST


START_TEST(test_hashtable_can_load_file)
{
	FILE *f_dale_list = fopen("lists/dale3000", "r");

	struct hash_table *dale_ht = hashtable_create(3000);

	ck_assert(f_dale_list != NULL);

	hashtable_load_lines_from_file(dale_ht, f_dale_list, 3000);

}
END_TEST

Suite * hashtable_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Hashtable");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_hashtable_can_create);
	tcase_add_test(tc_core, test_hashtable_can_insert);
	tcase_add_test(tc_core, test_hashtable_can_find_word);
	tcase_add_test(tc_core, test_hashtable_can_remove);
	tcase_add_test(tc_core, test_hashtable_can_be_full);
	tcase_add_test(tc_core, test_hashtable_can_load_file);
	suite_add_tcase(s, tc_core);

	return s;
}

/* IO tests

int can_count_zero_words();
int can_count_one_word();
int can_count_50_words_on_line();
int can_count_split_word_as_one();

int can_count_zero_sentences();
int can_count_one_sentence();
int can_count_split_sentences();

int can_get_words_from_string();

*/

START_TEST(test_io_can_count_zero_words)
{
	ck_assert(count_words("") == 0);
}
END_TEST

START_TEST(test_io_can_count_one_word)
{
	ck_assert(count_words("Hello!") == 1);
}
END_TEST

START_TEST(test_io_can_count_50_words_on_line)
{
	char * s = "Lorem ipsum dolor sit amet, consectetur\
	adipiscing elit. Nulla in molestie est. Nulla viverra nisl quis justo \
	dignissim consectetur. Phasellus sollicitudin lacinia ex eget fermentum.\
	Proin ac mi dolor. Nam tellus urna, ultricies et sem eu, scelerisque \
	molestie purus. Praesent dignissim justo et magna vestibulum facilisis.\
	 Quisque malesuada ex mollis.";

	ck_assert(count_words(s) == 50);
}

START_TEST(test_io_can_count_split_word_as_one)
{
	char *s = ", temper-\n-amental!";

	ck_assert(count_words(s) == 1);
}
END_TEST

START_TEST(test_io_can_count_zero_sentences)
{
	int result = count_sentences("");
	printf("sentence count of \"%s\" == %d\n", "", result);
	ck_assert(result == 0);
}
END_TEST

START_TEST(test_io_can_count_one_sentence)
{
	int result = count_sentences("Hello!");
	printf("sentence count of \"%s\" == %d\n", "Hello!", result);
	ck_assert(result == 1);
}
END_TEST


START_TEST(test_io_can_count_split_sentences)
{
	char * s = "Hello,\n World!.!\n Goodbye,\nMars!!";
	int result = count_sentences(s);
	printf("sentence count of \"%s\" == %d\n", s, result);
	ck_assert(result == 2);
}
END_TEST

START_TEST(test_io_can_get_words_from_string)
{
	char * s = "Nova is the love of my life"; // 7 words
	size_t num_words = 7;
	char ** s_array = calloc(20, sizeof(char *));

	int array_made = words_array_from_string(s, num_words, s_array);

	printf("%ld\n", num_words);

	for (int i = 0; i < num_words; i++)
	{
		 printf("%s\n", s_array[i]);
	}

}
END_TEST

Suite * io_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("IO");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_io_can_count_zero_words);
	tcase_add_test(tc_core, test_io_can_count_one_word);
	tcase_add_test(tc_core, test_io_can_count_50_words_on_line);
	tcase_add_test(tc_core, test_io_can_count_split_word_as_one);
	tcase_add_test(tc_core, test_io_can_count_zero_sentences);
	tcase_add_test(tc_core, test_io_can_count_one_sentence);
	tcase_add_test(tc_core, test_io_can_count_split_sentences);
	tcase_add_test(tc_core, test_io_can_get_words_from_string);
	suite_add_tcase(s, tc_core);

	return s;
}

int test_file_score(const char * filename, double max_acceptable_score)
{
	FILE *fp = fopen(filename, "r");

	double score = assess_readability(fp);
	fclose(fp);
	return (score <= max_acceptable_score);
}

START_TEST(test_scoring_roysullivan)
{
	ck_assert(test_file_score("testdata/roysullivan3", 5.9));
}
END_TEST

START_TEST(test_scoring_electoralcollege)
{
	ck_assert(test_file_score("testdata/electoralcollege3", 7.9));
}
END_TEST

START_TEST(test_scoring_modelt)
{
	ck_assert(test_file_score("testdata/modelt4", 6.9));
}
END_TEST

START_TEST(test_scoring_raisedbydogs)
{
	ck_assert(test_file_score("testdata/raisedbydogs4", 6.9));
}
END_TEST

START_TEST(test_scoring_alchemy)
{
	ck_assert(test_file_score("testdata/alchemy5", 8.9));
}
END_TEST

START_TEST(test_scoring_nomads)
{
	ck_assert(test_file_score("testdata/nomads6", 9.0));
}
END_TEST

START_TEST(test_scoring_scientist)
{
	ck_assert(test_file_score("testdata/scientist", 8.0));
}
END_TEST

START_TEST(test_scoring_gettysburg)
{
	ck_assert(test_file_score("testdata/gettysburg", 7.5));
}
END_TEST

Suite * scoring_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Scoring");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_scoring_roysullivan);
	tcase_add_test(tc_core, test_scoring_electoralcollege);
	tcase_add_test(tc_core, test_scoring_modelt);
	tcase_add_test(tc_core, test_scoring_raisedbydogs);
	tcase_add_test(tc_core, test_scoring_alchemy);
	tcase_add_test(tc_core, test_scoring_nomads);
	tcase_add_test(tc_core, test_scoring_scientist);
	tcase_add_test(tc_core, test_scoring_gettysburg);
	suite_add_tcase(s, tc_core);

	return s;
}

// Trie suite

START_TEST(test_trie_creation)
{
	struct TrieNode * trie_root = create_trie_node();

	ck_assert(trie_root != NULL);
}
END_TEST

START_TEST(test_trie_insertion)
{
	struct TrieNode * trie_root = create_trie_node();

	trie_insert(trie_root, "hello");	

	ck_assert(trie_contains(trie_root, "hello"));
}
END_TEST

START_TEST(test_trie_overlapping_insertion)
{
	struct TrieNode * trie_root = create_trie_node();

	trie_insert(trie_root, "hello");
	trie_insert(trie_root, "hell");
	trie_insert(trie_root, "he");

	ck_assert(trie_contains(trie_root, "hello"));
	ck_assert(trie_contains(trie_root, "hell"));
	ck_assert(trie_contains(trie_root, "he"));
}
END_TEST

START_TEST(test_trie_subtrie)
{

}
END_TEST

START_TEST(test_trie_large_input)
{
	const char *words[] = {
	"apple", "banana", "cherry", "dog", "elephant", "flower", "guitar", 
	"house", "igloo", "jungle", "kangaroo", "lemon", "mountain", 
	"notebook", "ocean", "penguin", "quilt", "rainbow", "sunset", "tiger",
	"umbrella", "violet", "waterfall", "xylophone", "yellow", "zebra", 
	"airplane", "basketball", "candle", "diamond", "eagle", "fountain", 
	"giraffe", "happiness", "icecream", "jazz", "kiwi", "lighthouse", 
	"moonlight", "noodle","orchestra", "puzzle", "quasar", "rhythm", 
	"sunflower", "trampoline", "unicorn", "vortex", "whisper", "xylograph",
	"yo-yo", "zephyr", "astronomy", "broccoli", "carousel", "dolphin", 
	"enigma", "fantasy", "gazelle", "harmony", "illusion", "jubilee", 
	"kaleidoscope", "lullaby", "mermaid", "nostalgia", "oblivion", 
	"pandemonium", "quicksilver", "reverie", "serendipity", "triumph", 
	"utopia", "volcano", "whimsical", "xanadu", "yearning", "zenith", 
	"ambrosia", "blossom", "cacophony", "dexterity", "ephemeral", 
	"fandango", "gossamer", "halcyon", "insouciant", "juxtapose", 
	"kismet", "labyrinth", "mellifluous", "nirvana", "opulent", 
	"quintessence", "resplendent", "serene", "talisman", "umbrage", 
	"vivid", "wanderlust", "xenial", "yonder", "zephyr", "acquiesce", 
	"benevolent", "cacophony", "dawdle", "effervescent", "felicity", 
	"garrulous", "higgledy-piggledy", "indefatigable", "juxtapose", 
	"kaleidoscope", "loquacious", "mellifluous", "noodle", "obfuscate", 
	"plethora", "quixotic", "resplendent", "serendipity", "talisman", 
	"ubiquitous", "vexatious", "whimsical", "xanadu", "yonder", "zeppelin"
	};
	const int num_words = 127;

	struct TrieNode * trie_root = create_trie_node();

	for (int i = 0; i < num_words; i++)
		trie_insert(trie_root, words[i]);

	for (int i = 0; i < num_words; i++)
		ck_assert(trie_contains(trie_root, words[i]));
}
END_TEST

Suite * trie_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Trie");

	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_trie_creation);
	tcase_add_test(tc_core, test_trie_insertion);
	tcase_add_test(tc_core, test_trie_overlapping_insertion);
	tcase_add_test(tc_core, test_trie_subtrie);
	tcase_add_test(tc_core, test_trie_large_input);
	suite_add_tcase(s, tc_core);

	return s;
}
int main(void)
{
	int number_failed = 0;
	Suite *s;
	SRunner *sr;

	// hash table suite
	s = hashtable_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed += srunner_ntests_failed(sr);
	srunner_free(sr);

	// IO suite
	s = io_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed += srunner_ntests_failed(sr);
	srunner_free(sr);

	// scoring suite
	s = scoring_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed += srunner_ntests_failed(sr);
	srunner_free(sr);

	// trie suite
	s = trie_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed += srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
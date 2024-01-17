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

	hashtable_load_words_from_file(dale_ht, f_dale_list, 3000);

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

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	// hash table suite
	s = hashtable_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
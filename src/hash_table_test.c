/*
 * August 5th, 2023
 *
 * hash_table_test.c
 *
 * Alex McColm
 *
 * Tests for the hash table implementation.
 */
#include "hash_table.h"
#include "test_utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <regex.h>

// Test case forward declarations
int can_create();
int can_insert();
int can_find_word();
int cannot_find_missing_word();
int can_remove();
int can_be_full();
int can_resize();
int can_load_file();

int main(void)
{
	int test_num = 0;
	
	/*
	announce_test(test_num, "Creating a HT", &can_create); 
	test_num++;
	*/
	RUN_TEST(can_create)

	announce_test(test_num, "Can insert string", &can_create); 
	test_num++;

	announce_test(test_num, "If inserted, HT contains string", 	&can_find_word); 
	test_num++;

	announce_test(test_num, "If not inserted, HT does not contain string", &cannot_find_missing_word); 
	test_num++;

	announce_test(test_num, "Can remove string from HT", &can_remove); 
	test_num++;

	announce_test(test_num, "100 strings can be inserted to HT", &can_be_full); 
	test_num++;

	announce_test(test_num, "Can resize list", &can_resize); 
	test_num++;

	announce_test(test_num, "Can load Dale's 769 easy words from file", &can_load_file); 
	test_num++;
}

// Test case definitions
int can_create()
{
	struct hash_table *ht = hashtable_create(10);
	hashtable_print_contents(ht, stdout);
	return 1;
}

int can_insert()
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	hashtable_print_contents(ht, stdout);
	return 1;
}

int can_find_word()
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	return hashtable_contains(ht, "Hello");
}

int cannot_find_missing_word()
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	return (!hashtable_contains(ht, "Boots"));
}

int can_be_full()
{
	struct hash_table *ht = hashtable_create(200);

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

	printf("%d words of 100 added.\n", successful_adds);

	hashtable_print_contents(ht, stdout);

	return 1;
}

int can_remove()
{
	struct hash_table *ht = hashtable_create(10);
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	hashtable_remove(ht, word);
	return (!hashtable_contains(ht, word));
}

int can_resize()
{
	struct hash_table *ht = hashtable_create(10);

	hashtable_insert(ht, "Hello");
	hashtable_insert(ht, "Bello");
	hashtable_insert(ht, "Mello");
	hashtable_insert(ht, "Yello");
	hashtable_insert(ht, "Sello");

	ht = hashtable_resize(ht, 100);
	printf("Size now %d\n", ht->array_size);

	hashtable_print_contents(ht, stdout);

	ht = hashtable_resize(ht, 200);
	printf("Size now %d\n", ht->array_size);

	hashtable_print_contents(ht, stdout);

	return (ht->array_size == 200);
}

int can_load_file()
{
	FILE *f_dale_list = fopen("dale list of 769 easy words", "r");

	struct hash_table *dale_ht = hashtable_create(3000);

	if (f_dale_list == NULL)
		return 0;

	hashtable_load_words_from_file(dale_ht, f_dale_list, 1500);

	hashtable_print_contents(dale_ht, stdout);

	return 1;
}
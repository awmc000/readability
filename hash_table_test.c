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
#include <string.h>
#include <stdlib.h>

// Test case forward declarations
void can_create();
void can_insert();
void can_find_word();
void cannot_find_missing_word();
void can_remove();
void can_be_full();
void can_resize();

// TODO: Reduce duplication of PASS/FAIL prints, put that in this function
// by turning all the test functions above ^ to return int success or fail.
void announce_test(int count, char * name/*, int result*/)
{
	printf("\n\n\n========== TEST %d, %s ==========\n\n\n", count, name);
}

int main(void)
{
	int test = 0;

	announce_test(test, "Creating a HT"); test++;
	can_create();

	announce_test(test, "Can insert string"); test++;
	can_insert();

	announce_test(test, "Can check if HT contains string"); test++;
	can_find_word();

	announce_test(test, "Can check if HT does not contain string"); test++;
	cannot_find_missing_word();

	announce_test(test, "Can remove string from HT"); test++;
	can_remove();

	announce_test(test, "100 strings can be inserted to HT"); test++;
	can_be_full();

	announce_test(test, "Can resize list"); test++;
	can_resize();
}

// Test case definitions
void can_create()
{
	struct hash_table *ht = hashtable_create();
	hashtable_print_contents(ht, stdout);
}

void can_insert()
{
	struct hash_table *ht = hashtable_create();
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	hashtable_print_contents(ht, stdout);
}

void can_find_word()
{
	struct hash_table *ht = hashtable_create();
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	int found_word = hashtable_contains(ht, "Hello");
	if (found_word == 1)
	{
		printf("\nPASS!\n");
	}
	else
	{
		printf("\nFAILED!\n");
	}
}

void cannot_find_missing_word()
{
	struct hash_table *ht = hashtable_create();
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);

	int found_word = hashtable_contains(ht, "Boots");
	if (found_word == 0)
	{
		printf("\nPASS!\n");
	}
	else
	{
		printf("\nFAILED!\n");
	}
}

void can_be_full()
{
	struct hash_table *ht = hashtable_create();

	const char* words[100] = {
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
		"ziziphus", "acai", "safou", "breadnut", "damson plum", "gac", 
		"carambola", "quandong", "guava", "lingonberry", "gooseberry"
	};

	for (int i = 0; i < 100; i++)
	{
		hashtable_insert(ht, words[i]);
	}

	hashtable_print_contents(ht, stdout);
}

void can_remove()
{
	struct hash_table *ht = hashtable_create();
	char *word = calloc(5 + 1, sizeof(char));
	strcpy(word, "Hello");
	hashtable_insert(ht, word);
	hashtable_remove(ht, word);
	if (!hashtable_contains(ht, word))
	{
		printf("Passed!\n");
	}
	else
	{
		printf("Failed!\n");
	}
}

void can_resize()
{
	struct hash_table *ht = hashtable_create();

	ht = hashtable_resize(ht, 2 * INITIAL_SIZE);
	printf("Size now %d\n", ht->array_size);

	/*ht = hashtable_resize(ht, 2 * ht->array_size);
	printf("Size now %d\n", ht->array_size);

	ht = hashtable_resize(ht, 2 * ht->array_size);
	printf("Size now %d\n", ht->array_size);
	*/

	hashtable_insert(ht, "Hello");
	hashtable_insert(ht, "Bello");
	hashtable_insert(ht, "Mello");
	hashtable_insert(ht, "Yello");
	hashtable_insert(ht, "Sello");

	// Segfaults at i == 100... array member alloc issue?
	hashtable_print_contents(ht, stdout);

}
/*
 * trie.h
 *
 * January 16th, 2024
 *
 * Trie data structure for storing a large quantity of strings.
 *
 */
#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 27 // a-z plus space

struct TrieNode
{
	struct TrieNode * links[ALPHABET_SIZE];
	unsigned int num_links: 4;
	unsigned int is_terminal : 1; // bit flag
};

/**
 * @brief Allocates a TrieNode on the heap.
 **/
struct TrieNode * create_trie_node();

/**
 * @brief Tries to navigate to the last char in a string.
 * @param str Search key.
 * @return Pointer to the TrieNode representing the last letter
 * in the string or NULL if not found.
 **/
struct TrieNode * subtrie(struct TrieNode * trie, const char * search_key);

/**
 * @brief Adds a string to a Trie.
 * @param trie Root node of trie which does not represent any letter.
 * @return 1 if inserted and 0 on error.
 **/
int trie_insert(struct TrieNode * trie, const char * value);


/**
 * @brief Checks if the Trie contains a string.
 * @param trie Root node of trie which does not represent any letter.
 * @return 1 if found and 0 if not found or error.
 **/
int trie_contains(struct TrieNode * trie, const char * search_key);

/**
 * @brief Recursively frees every element in a Trie.
 **/
void trie_destroy(struct TrieNode * trie);

#endif // TRIE_H

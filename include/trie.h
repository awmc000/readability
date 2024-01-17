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
	struct TreeNode * links[ALPHABET_SIZE];
	unsigned int num_links: 4;
	unsigned int is_terminal : 1; // bit flag
};

struct TrieNode * create_trie();
int trie_insert(struct TrieNode * trie, const char * value);
int trie_contains(struct TrieNode * trie, const char * search_key);

#endif // TRIE_H

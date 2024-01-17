#include "trie.h"
#include <stdlib.h>

struct TrieNode * create_trie()
{

	return calloc(1, sizeof(struct TrieNode));
}

int trie_insert(struct TrieNode * trie, const char * value)
{
	return -1;
}

int trie_contains(struct TrieNode * trie, const char * search_key)
{
	return -1;
}

// test driver
int main(void)
{
	return 0;
}

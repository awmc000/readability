#include "trie.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int char_to_index(char c)
{
	if (isspace(c))
		return 0;

	return toupper(c) - 'A' + 1;
}


struct TrieNode * create_trie_node()
{
	return calloc(1, sizeof(struct TrieNode));
}

int trie_insert(struct TrieNode * trie, const char * str)
{
	struct TrieNode * curr = trie;
	struct TrieNode * next;

	while (*str != '\0')
	{
		// Create a node for the next letter
		next = create_trie_node(*str);

		// Add it to the links of the current node
		curr->links[char_to_index(*str)] = next;
		curr->num_links++;

		// The next node is the new current node
		curr = next;

		// Advance to next char in string
		str++;
	}

	next->is_terminal = 1;

	printf("{%d}\n", next != NULL);

	return -1;
}

int trie_contains(struct TrieNode * trie, const char * search_key)
{
	return -1;
}

// test driver
int main(void)
{
	printf("%c: %d\n", ' ', char_to_index(' '));

	for (int i = 'A'; i <= 'Z'; i++)
	{
		printf("%c: %d\n", i, char_to_index(i));
	}

	struct TrieNode * root_node = create_trie_node();
	trie_insert(root_node, "ace");

	printf("%d %d %d %d\n",
		root_node->links[1] != NULL,
		root_node->links[1]->links[3] != NULL,
		root_node->links[1]->links[3]->links[5] != NULL,
		root_node->links[25] == NULL);

	return 0;
}

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

struct TrieNode * subtrie(struct TrieNode * trie, const char * search_key)
{
	while (*search_key != '\0')
	{
		trie = trie->links[char_to_index(*search_key)];
		search_key++;
		if (trie == NULL)
			return NULL;
	}
	return trie;

}

int trie_insert(struct TrieNode * trie, const char * str)
{
	struct TrieNode * curr = trie;
	struct TrieNode * next;

	while (*str != '\0')
	{
		int index = char_to_index(*str);
		// Find or Create a node for the next letter
		if (curr->links[index] == NULL)
			next = create_trie_node(*str);
		else
			next = curr->links[index];

		// Add it to the links of the current node
		curr->links[index] = next;
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
	struct TrieNode * sub_trie = subtrie(trie, search_key);
	if (sub_trie == NULL)
		return 0;

	return (subtrie != NULL) && (sub_trie->is_terminal);
}

// test driver
int main(void)
{

	struct TrieNode * root_node = create_trie_node();
	trie_insert(root_node, "ace");
	trie_insert(root_node, "aced");
	trie_insert(root_node, "far");
	trie_insert(root_node, "yes");

//	printf("%d\n", subtrie(root_node, "a")->links[3] != NULL);

	printf("%d\n", trie_contains(root_node, "ace"));
	printf("%d\n", trie_contains(root_node, "aced"));
	printf("%d\n", trie_contains(root_node, "far"));
	printf("%d\n", trie_contains(root_node, "yes"));

	return 0;
}

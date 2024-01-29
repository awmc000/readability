#include "trie.h"
#include "util.h"
#include <stdlib.h>
#include <ctype.h>

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
	return -1;
}

int trie_contains(struct TrieNode * trie, const char * search_key)
{
	struct TrieNode * sub_trie = subtrie(trie, search_key);
	if (sub_trie == NULL)
		return 0;

	return (subtrie != NULL) && (sub_trie->is_terminal);
}

void trie_destroy(struct TrieNode * trie)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (trie->links[i] != NULL)
			trie_destroy(trie->links[i]);
	}

	free(trie);

	return;
}


struct TrieNode * trie_from_file(FILE * fp)
{
	struct TrieNode * trie = create_trie_node();

	// Set up buffer for file
	char * buf_line = calloc(256, sizeof(char));
	size_t buf_size = 0;

	while ( getline(&buf_line, &buf_size, fp) != -1 )
	{
		char * this_word = extract_word(buf_line);
		trie_insert(trie, this_word);
	}

	return trie;	
}

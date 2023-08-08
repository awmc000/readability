main : main.o hash_table.o trie.o
	gcc -o readability main.o hash_table.o trie.o -g
	./readability test-text

debug: main.c hash_table.c hash_table.h trie.c trie.h test_utils.h
	gcc -o debug -g main.c hash_table.c trie.c
main.o: main.c
	gcc -c main.c -g

hash_table.o: hash_table.c hash_table.h
	gcc -c hash_table.c -g

trie.o: trie.c trie.h
	gcc -c trie.c -g

test_ht: hash_table_test.c hash_table.c hash_table.h test_utils.h
	gcc -o hash_table_test hash_table_test.c hash_table.c -g
	./hash_table_test

clean:
	rm readability main.o hash_table.o trie.o hash_table_test

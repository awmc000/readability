main : main.o hash_table.o trie.o
	gcc -o readability main.o hash_table.o trie.o
	./readability

main.o: main.c
	gcc -c main.c

hash_table.o: hash_table.c hash_table.h
	gcc -c hash_table.c

trie.o: trie.c trie.h
	gcc -c trie.c

test_hash_table: hash_table_test.c hash_table.c hash_table.h
	gcc -o hash_table_test hash_table_test.c hash_table.c
	./hash_table_test

clean:
	rm readability main.o hash_table.o trie.o
	rm hash_table_test

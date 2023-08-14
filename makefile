main : main.o hash_table.o test_utils.o io.o
	gcc -o readability main.o hash_table.o io.o -g
	./readability testdata/test-text

debug: main.c hash_table.c hash_table.h test_utils.h test_utils.c io.h io.c
	gcc -o debug -g main.c hash_table.c test_utils.c io.c

main.o: main.c
	gcc -c main.c -g

hash_table.o: hash_table.c hash_table.h
	gcc -c hash_table.c -g

test_utils.o: test_utils.c test_utils.h
	gcc -c test_utils.c

io.o: io.h io.c
	gcc -c io.c

test_ht: hash_table_test.c hash_table.c hash_table.h test_utils.h test_utils.c
	gcc -o test_ht hash_table_test.c hash_table.c test_utils.c -g
	./test_ht

test_io: io.c io.h io_test.c test_utils.c test_utils.h
	gcc -g -o test_io io.c io_test.c test_utils.c
	./test_io

clean:
	rm -f readability main.o hash_table.o test_ht test_io debug

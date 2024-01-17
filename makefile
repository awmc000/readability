INCLUDES=-Iinclude/
HEADERS=include/hash_table.h include/io.h include/scoring.h include/test_utils.h include/trie.h
SOURCES=src/hash_table.c src/io.c src/scoring.c src/trie.c

main : main.o hash_table.o test_utils.o io.o scoring.o
	gcc -Wall -o readability main.o hash_table.o io.o scoring.o
	./readability testdata/gettysburg

# x86_64-w64-mingw32-gcc
win64: src/main.c src/hash_table.c include/hash_table.h \
include/test_utils.h src/test_utils.c include/io.h src/io.c \
include/scoring.h
	x86_64-w64-mingw32-gcc -o readability_win64.exe ${INCLUDES} src/main.c src/hash_table.c \
	src/test_utils.c src/io.c src/scoring.c

debug: src/main.c src/hash_table.c include/hash_table.h \
include/test_utils.h src/test_utils.c include/io.h src/io.c \
include/scoring.h
	gcc -o debug -g ${INCLUDES} src/main.c src/hash_table.c \
	src/test_utils.c src/io.c src/scoring.c
	gdb debug

main.o: src/main.c
	gcc ${INCLUDES} -c src/main.c -g

hash_table.o: src/hash_table.c include/hash_table.h
	gcc ${INCLUDES} -c src/hash_table.c -g

test_utils.o: src/test_utils.c include/test_utils.h
	gcc ${INCLUDES} -c src/test_utils.c

io.o: include/io.h src/io.c
	gcc ${INCLUDES} -c src/io.c

scoring.o: include/scoring.h src/scoring.c
	gcc ${INCLUDES} -c src/scoring.c

test: ${SOURCES} src/test.c ${HEADERS}
	gcc ${INCLUDES} ${SOURCES} src/test.c -o test -lcheck -lm -lsubunit
	./test

test_ht: src/hash_table_test.c src/hash_table.c include/hash_table.h include/test_utils.h \
src/test_utils.c
	gcc ${INCLUDES} -o test_ht src/hash_table_test.c src/hash_table.c src/test_utils.c -g
	./test_ht

test_io: src/io.c include/io.h src/io_test.c src/test_utils.c include/test_utils.h
	gcc ${INCLUDES} -g -o test_io src/io.c src/io_test.c src/test_utils.c
	./test_io

test_scoring: src/scoring_test.c scoring.o io.o test_utils.o hash_table.o
	gcc ${INCLUDES} -g -o test_scoring src/scoring_test.c scoring.o io.o test_utils.o hash_table.o
	./test_scoring

clean:
	rm -f readability main.o hash_table.o io.o scoring.o test_utils.o test_ht test_io test_scoring debug

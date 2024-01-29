INCLUDES=-Iinclude/
HEADERS=include/hash_table.h include/io.h include/scoring.h include/trie.h include/util.h
SOURCES=src/hash_table.c src/io.c src/scoring.c src/trie.c src/util.c

main : main.o hash_table.o io.o scoring.o trie.o util.o
	gcc -Wall -o readability main.o hash_table.o io.o scoring.o trie.o util.o
	./readability testdata/gettysburg

# x86_64-w64-mingw32-gcc
win64: src/main.c src/hash_table.c include/hash_table.h \
include/io.h src/io.c include/scoring.h
	x86_64-w64-mingw32-gcc -o readability_win64.exe ${INCLUDES} ${SOURCES}

debug: src/main.c src/hash_table.c include/hash_table.h \
include/io.h src/io.c include/scoring.h
	gcc -o debug -g ${INCLUDES} src/main.c src/hash_table.c \
	src/test_utils.c src/io.c src/scoring.c
	gdb debug

main.o: src/main.c
	gcc ${INCLUDES} -c src/main.c -g

hash_table.o: src/hash_table.c include/hash_table.h
	gcc ${INCLUDES} -c src/hash_table.c -g

io.o: include/io.h src/io.c
	gcc ${INCLUDES} -c src/io.c

scoring.o: include/scoring.h src/scoring.c
	gcc ${INCLUDES} -c src/scoring.c

trie.o: include/trie.h src/trie.c
	gcc ${INCLUDES} -c src/trie.c

util.o: include/util.h src/util.c
	gcc ${INCLUDES} -c src/util.c

test: ${SOURCES} src/test.c ${HEADERS}
	gcc ${INCLUDES} ${SOURCES} src/test.c -o test -lcheck -lm -lsubunit
	./test

clean:
	rm -f readability main.o hash_table.o io.o scoring.o test_utils.o test_ht test_io test_scoring debug test

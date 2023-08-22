INCLUDES=-Iinclude/

main : main.o hash_table.o test_utils.o io.o scoring.o
	gcc -o readability main.o hash_table.o io.o scoring.o -g
	./readability testdata/gettysburg

debug: src/main.c src/hash_table.c include/hash_table.h include/test_utils.h \
test_utils.c include/io.h src/io.c
	gcc -o debug -g src/main.c src/hash_table.c src/test_utils.c src/io.c
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
	rm -f readability main.o hash_table.o io.o scoring.o test_utils.o test_ht test_io debug

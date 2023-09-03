make
clear
valgrind --leak-check=full --show-leak-kinds=all ./readability \
	testdata/gettysburg

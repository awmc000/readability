#ifndef SCORING_H
#define SCORING_H

#include <regex.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "io.h"

void print_score_bracket(double dale_chall_score);
double assess_readability(FILE *text_file);
// struct hash_table *get_table_from_list_file(const char * filename, unsigned int words);

#endif // SCORING_H
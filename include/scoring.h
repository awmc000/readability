#ifndef SCORING_H
#define SCORING_H

#include <regex.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "io.h"

// If this macro is defined, the expanded Dale list is used.
// If not, the original 2950 words are used.
#define USE_EXPANDED_DALE_LIST 1

void print_score_bracket(double dale_chall_score);
double assess_readability(FILE *text_file);

#endif // SCORING_H
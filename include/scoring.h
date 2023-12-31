/*
 * August 16th, 2023
 *
 * scoring.h
 *
 * Alex McColm
 *
 * Functions for assessing Dale Chall readability score of a text.
 **/
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

#endif // SCORING_H
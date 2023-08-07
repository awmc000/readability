/*
 * August 6th, 2023
 *
 * test_utils.h
 *
 * Alex McColm
 *
 * Macros and functions for use in test frames for the hash table and trie that
 * are not directly related.
 **/
#ifndef TEST_UTILS_H
#define TEST_UTILS_H


// ANSI escape code to reset colors and formatting
#define ANSI_COLOR_RESET     "\x1b[0m"

// ANSI escape codes for colours
#define ANSI_COLOR_BLACK     "\x1b[30m"
#define ANSI_COLOR_RED       "\x1b[31m"
#define ANSI_COLOR_GREEN     "\x1b[32m"
#define ANSI_COLOR_YELLOW    "\x1b[33m"
#define ANSI_COLOR_BLUE      "\x1b[34m"
#define ANSI_COLOR_MAGENTA   "\x1b[35m"
#define ANSI_COLOR_CYAN      "\x1b[36m"
#define ANSI_COLOR_WHITE     "\x1b[37m"

// ANSI escape codes for background colors
#define ANSI_BG_COLOR_BLACK  "\x1b[40m"
#define ANSI_BG_COLOR_RED    "\x1b[41m"
#define ANSI_BG_COLOR_GREEN  "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW "\x1b[43m"
#define ANSI_BG_COLOR_BLUE   "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN   "\x1b[46m"
#define ANSI_BG_COLOR_WHITE  "\x1b[47m"

#endif
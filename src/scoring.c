/*
 * August 16th, 2023
 *
 * scoring.c
 *
 * Alex McColm
 *
 * Functions for assessing Dale Chall readability score of a text.
 **/
#include "scoring.h"

#define RATIO_PERCENTAGE(a, b) ( ( (double) a / (double) b ) * 100 )

void handle_load(int load_success, const char *desc)
{
	switch (load_success)
	{
	case 1:
		fprintf(stderr, "%s loaded successfully.\n", desc);
		break;
	case 0:
		fprintf(stderr, "%s failed to load.\n", desc);
		break;
	default:
		fprintf(stderr, "unknown load success code received!\n");
		break;
	}
}

void print_score_bracket(double dale_chall_score)
{

	printf("Easily understood by an average ");
	
	const char * score_descriptions[] = {
		"student in 4th grade or lower.\n",
		"student in 5th or 6th grade.\n",
		"student in 7th or 8th grade.\n",
		"student in 9th or 10th grade.\n",
		"student in 11th or 12th grade.\n",
		"college\n",
		"college graduate.\n",
	};

	if (dale_chall_score <= 9.9)
	{
		const char * matching_description = score_descriptions[( (int) dale_chall_score - 4) % 6];
		printf("%s", matching_description);
	}
	else
	{
		printf("college graduate.\n");
	}

}

struct hash_table *get_table_from_list_file(const char * filename, unsigned int words)
{
	struct hash_table *list_table   = hashtable_create(2 * words);

	// Load file of Lorge easy words list into hash table.
	FILE * list_fp = fopen(filename, "r");
	
	int load_success = hashtable_load_words_from_file(list_table, 
		list_fp, words);
	
	handle_load(load_success, filename);

	fclose(list_fp);

	return list_table;

}

int all_digits(const char * s)
{
	for (unsigned int i = 0; i < strlen(s); i++)
	{
		if (i > 5)
			break;
		if (!isdigit(s[i]))
		{
			return 0;
		}
	}

	return 1;
}

void print_report(int difficult_words, int total_words, 
	int total_sentences, float words_per_sent, float diff_pct,
	float score)
{
	printf("==== Breakdown ====\n"
		"HARD WORDS : %d\n"
		"TOTAL WORDS: %d\n"
		"SENTENCES  : %d\n"
		"AVG. WORDS / SENTENCE : %.2f\n"
		"PCT. DIFFICULT WORDS  : %.2f\n"
		"DALE-CHALL READABILITY: %.3f\n",
		difficult_words, total_words, total_sentences,
		words_per_sent, diff_pct, score);


	print_score_bracket(score);
}

void count_easy_words(char ** word_arr, int words, int *p_easy_words,
	struct hash_table *easy_words, struct hash_table *proper_nouns)
{
	for (unsigned int i = 0; i < words; i++)
	{
		if (all_digits(word_arr[i]) ||
			(hashtable_contains(easy_words, word_arr[i])) ||
			(hashtable_contains(proper_nouns, word_arr[i])))
		{
			(*p_easy_words)++;
		}
		// free each word after use
		free(word_arr[i]);
	}
}

void count_words_in_file(FILE* text_fp, int *p_total_sentences, 
	int *p_total_words, int *p_easy_words_count,
	struct hash_table *easy_words, struct hash_table * proper_nouns)
{
	// Set up the buffer for line-by-line text reading.
	char * buf_line = calloc(256, sizeof(char));
	size_t buf_size = 0;
	int words, sentences;
	while ( getline(&buf_line, &buf_size, text_fp) != -1 )
	{
		// count sentences and words in the line
		sentences = count_sentences(buf_line);
		words = count_words(buf_line);
		
		// add to text totals
		(*p_total_sentences) += sentences;
		(*p_total_words) += words;

		// put words in a special array
		size_t num_words = words;
		char ** word_arr = calloc(2 * words, sizeof(char *));
		size_t *word_arr_elems;

		int array_creation_success = words_array_from_string(
			buf_line, num_words, word_arr);

		// Count the easy words in the word array
		count_easy_words(word_arr, words, p_easy_words_count, easy_words,
			proper_nouns);

		// Free the word array
		free(word_arr);
	}

	free(buf_line);

	hashtable_delete(easy_words);
	free(easy_words);

	hashtable_delete(proper_nouns);
	free(proper_nouns);
}

double assess_readability(FILE *text_file)
{
	// Counter variables for computing the score.
	int total_sentences = 0, sentences = 0;
	int total_words = 0, words = 0;

	int easy_words_count = 0;

	// Set up hash tables for easy words and proper nouns
	struct hash_table *easy_words = get_table_from_list_file(
		"lists/dale-expanded", 14921);

	struct hash_table *proper_nouns = get_table_from_list_file(
		"lists/proper-nouns", 5742);

	count_words_in_file(text_file, 
		&total_sentences, &total_words, &easy_words_count, 
		easy_words, proper_nouns);

	if (total_sentences == 0 || total_words < 5)
	{
		printf("Invalid input. Enter at least one sentence"
			" with 5 words to receive a readability score.\n");
		return -1.0;
	}

	int difficult_words = total_words - easy_words_count;

	double diff_pct = RATIO_PERCENTAGE(difficult_words, total_words);
	
	double words_per_sent = (double) total_words / 
	(double) total_sentences;

	double score = 0.1579 * diff_pct +  (0.0496 * words_per_sent);

	if (diff_pct > 5.0)
		score += 3.6365;

	print_report( difficult_words, total_words, 
		total_sentences, words_per_sent, diff_pct, score);

	return score;
}
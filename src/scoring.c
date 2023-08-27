#include "scoring.h"
#include <time.h>
typedef long nanosecond;

//#define PRINT_HARD_WORDS 1

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
	
	if (dale_chall_score <= 4.9)

		printf("student in 4th grade or lower.\n");
	
	else if (dale_chall_score <= 5.9)
	
		printf("student in 5th or 6th grade.\n");
	
	else if (dale_chall_score <= 6.9)
	
		printf("student in 7th or 8th grade.\n");
	
	else if (dale_chall_score <= 7.9)
	
		printf("student in 9th or 10th grade.\n");
	
	else if (dale_chall_score <= 8.9)
	
		printf("student in 11th or 12th grade.\n");
	
	else if (dale_chall_score <= 9.9)
	
		printf("college\n");
	
	else
	
		printf("college graduate.\n");
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

int all_digits(char * s)
{
	for (unsigned int i = 0; i < strlen(s); i++)
	{
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

double assess_readability(FILE *text_file)
{
	struct timespec res;
	nanosecond before, after;
	clock_gettime(CLOCK_REALTIME, &res);
	before = res.tv_nsec;
	
	// Set up the buffer for line-by-line text reading.
	char * buf_line = calloc(256, sizeof(char));
	size_t buf_size = 0;

	// Counter variables for computing the score.
	int total_sentences = 0, sentences = 0;
	int total_words = 0, words = 0;

	int easy_words_count = 0;

	// Set up hash tables for Dale list of easy words 
	// and list of proper nouns 
	struct hash_table *easy_words = get_table_from_list_file(
		"lists/dale-expanded", 14921);

	struct hash_table *proper_nouns = get_table_from_list_file(
		"lists/proper-nouns", 5742);

	// Count sentences and words.
	while ( getline(&buf_line, &buf_size, text_file) != -1 )
	{
		// count sentences and words in the line
		sentences = count_sentences(buf_line);
		words = count_words(buf_line);
		
		// add to text totals
		total_sentences += sentences;
		total_words += words;

		// put words in a special array
		size_t num_words = words;
		char ** word_arr = calloc(2 * words, sizeof(char *));
		size_t *word_arr_elems;

		int array_creation_success = words_array_from_string(
			buf_line, num_words, word_arr);

		// Check if each word is an easy word
		for (unsigned int i = 0; i < words; i++)
		{
			if (all_digits(word_arr[i]))
			{
				easy_words_count++;
			}
			if (hashtable_contains(easy_words, word_arr[i]))
			{
				easy_words_count++;
			}
			else if (hashtable_contains(proper_nouns, word_arr[i]))
			{
				easy_words_count++;
			}
			#ifdef PRINT_HARD_WORDS
				else if (PRINT_HARD_WORDS)
				{
						printf("%s is a hard word.\n", word_arr[i]);

				}
			#endif
			
			// free each word after use
			free(word_arr[i]);
		}

		// When we were not freeing each word, this would leave
		// as many dangling pointers as there were words in the text!
		free(word_arr);
	}

	free(buf_line);

	hashtable_delete(easy_words);
	free(easy_words);

	hashtable_delete(proper_nouns);
	free(proper_nouns);

	if (total_sentences == 0 || total_words < 5)
	{
		printf("Invalid input. Enter at least one sentence"
			" with 5 words to receive a readability score.\n");
		return -1.0;
	}

	int difficult_words = total_words - easy_words_count;

	double diff_pct = (double) difficult_words / 
		(double) total_words * 100.0;
	
	double words_per_sent = (double) total_words / 
		(double) total_sentences;

	double score = 0.1579 * diff_pct +  (0.0496 * words_per_sent);

	if (diff_pct > 5.0)
		score += 3.6365;

	print_report( difficult_words, total_words, 
		total_sentences, words_per_sent, diff_pct, score);

	// Get the completion time
	clock_gettime(CLOCK_REALTIME, &res);
	after = res.tv_nsec;
	// Take the difference and divide by one million for milliseconds
	nanosecond diff = after - before;

	printf("Computed score in %.4Lf ms.\n", (long double)diff / 1000000L);

	return score;
}
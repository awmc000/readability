# ###################################################################
# create_expanded_list.py
#
# Created August 21st, 2023
# by Alex McColm
#
# Purpose: Take Dale's list of ~3000 easy words, and use the 
# word_forms module to write a new list containing every single form
# of the words in the previous list.
# ###################################################################
import os
import sys
from word_forms.word_forms import get_word_forms

def main() -> int:
	# Open original list and new list files.
	original_file = open('dale3000', 'r')
	new_file = open('dale-expanded', 'w')

	line = original_file.readline()

	# For each line in the old file
	while line != '':
		# Get rid of newline
		word = line.strip()

		# Get dictionary of word forms, sorted by word type
		forms_dict = get_word_forms(word)

		# Put all other type of word forms into a list.
		form_list = []

		for i in list(forms_dict.values()):
			for j in i:
				form_list.append(j)

		# Filter out word forms longer than 10 letters
		form_list = list(filter(
			lambda word: (len(word) < 11), form_list))

		# Convert to a set to get rid of duplicates.
		form_set = set(form_list)

		# Add the original word to the set.
		form_set.add(word)

		# Write to expanded list file followed by newline.
		for form in form_set:
			new_file.write(form + '\n')

		# Go to the next line.
		line = original_file.readline()

	# Close original list and new list files.
	original_file.close()
	new_file.close()
	return 0

if __name__ == '__main__':
	sys.exit(main())
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
from word_forms.word_forms import get_word_forms

# Open original list and new list files.
original_list = open('dale3000', 'r')
new_list = open('dale-expanded', 'w')


# For each line in the old file,
# 	For each word in the line,
# 		Get a list of forms of that word.
# 		Add all forms to the new file.
line = original_list.readline()

while line != '':
	word = line.strip()
	print('For ' + word, sep = '')

	# Get dictionary of word forms, sorted by word type
	forms_dict = get_word_forms(word)
	del forms_dict['n']
	form_list = []
	for i in list(forms_dict.values()):
		for j in i:
			form_list.append(j)

	# filter out word forms longer than 10 letters
	form_list = list(filter(
		lambda word: (len(word) < 11), form_list))

	form_set = set(form_list)

	for form in form_set:
		new_list.write(form + '\n')
		print(form, sep = ' ')
	print('')

	# Go to the next line.
	line = original_list.readline()

# Close original list and new list files.
original_list.close()
new_list.close()
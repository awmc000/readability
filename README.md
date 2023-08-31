# readability
Estimate readability of text using the Dale Chall formula.

# Usage

To compute the readability score of a text file named `story.txt`, you would run 
this command in the directory where both `readability` and `story.txt` reside.
```sh
./readability story.txt
```
If the `readability` binary and `story.txt` were in different locations, you 
might use something like this instead:
```sh
readability ~/Documents/story.txt
```

# Example Output

```sh
./readability testdata/modelt4
READABILITY OF "testdata/modelt4"
==== Breakdown ====
HARD WORDS : 63
TOTAL WORDS: 535
SENTENCES  : 44
AVG. WORDS / SENTENCE : 12.16
PCT. DIFFICULT WORDS  : 11.78
DALE-CHALL READABILITY: 6.099
Easily understood by an average student in 7th or 8th grade.
````

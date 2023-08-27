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
./readability testdata/gettysburg
testdata/gettysburg
==== Breakdown ====
HARD WORDS : 38
TOTAL WORDS: 270
SENTENCES  : 10
AVG. WORDS / SENTENCE : 27.00
PCT. DIFFICULT WORDS  : 14.07
DALE-CHALL READABILITY: 7.198
Easily understood by an average student in 9th or 10th grade.
Computed score in 24.6647 ms.
````


# Credits

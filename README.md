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
lists/dale-expanded loaded successfully.
lists/proper-nouns loaded successfully.
Freed 14921 strings from a ht with 0 elemsand total size 29842.
Freed 0 strings from a ht with 5742 elemsand total size 11484.
Dale-Chall score of 7.20
Breakdown: 38 hard of 270 words, 10 sentences.
 avg. 27 words per sentence. 14.07% difficult words.
Easily understood by an average student in 9th or 10th grade
Computed score in 20.6788 ms.

````


# Credits

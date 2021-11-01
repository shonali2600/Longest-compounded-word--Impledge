
# Longest compounded word

`A compounded word is one that can be constructed by combining (concatenating) shorter words also found in the same file`

1. Reads provided files `(Input_01.txt and Input_02.txt)` containing alphabetically sorted words list (one word per line, no spaces, all lower case)

2. Identifies & display below given data in logs/console/output file

- Longest compounded word

- Second longest compounded word

- Time taken to process the input file

## Approach:

1. The problem consisted of traversing strings character by character. This
   suggested the use of `Trie (prefix) tree`. Trie tree gives a `O(m) search-time`
   for a word, where 'm' is word length. This program needs to keep track of
   all the valid words in a compound word, which can be done conveniently in trie.

2. To check if a word is a compound word, the program traverses the string
   character by character, till it finds a complete word from the trie. It then
   recursively checks whether the remaining part is also a word OR a compound word.

3. The worst-case time complexity to check whether a word is compound is O(m^2),
   where 'm' is word length. Hence, for 'n' words, the time complexity is O(n.m^2).
   The word length 'm' is very small for a large dataset.


## Run Locally

Clone the project

```bash
  git clone https://github.com/shonali2600/Longest-compounded-word--Impledge.git
```

Go to the project directory

```bash
  cd Longest-compounded-word--Impledge
```

Run the program

```bash
  Compile and run the program
  Enter the input file name (ex: Input_01.txt OR Input_02.txt)
  
```

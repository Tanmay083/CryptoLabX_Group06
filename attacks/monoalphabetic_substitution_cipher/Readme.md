# Assignment 5 - Monoalphabetic Substitution Cipher and its Cryptanalysis Using Frequency and Pattern Analysis

## Group Members

- Lokesh
- Parth

## Objective

The objective of this assignment is to implement a Monoalphabetic Substitution Cipher and perform its cryptanalysis using letter-frequency analysis, word-frequency analysis, and pattern analysis.

The program encrypts plaintext using a monoalphabetic substitution key and then helps in recovering the plaintext and substitution key through iterative cryptanalysis.

## Plaintext

The plaintext is taken from **Page 38** of *Introduction to Modern Cryptography* by Katz and Lindell.

The text is stored in:

```text
plaintext.txt
```

The C++ program reads the plaintext directly from this file.

## Language Used

C++

## Features

The program performs the following operations:

- Reads plaintext from a text file
- Encrypts plaintext using a monoalphabetic substitution cipher
- Generates the ciphertext
- Performs letter-frequency analysis
- Calculates the count and percentage frequency of each letter
- Displays letters in descending order of frequency
- Identifies the most frequent ciphertext letters
- Performs word-frequency analysis
- Identifies one-letter, two-letter, and three-letter words
- Identifies repeated words
- Performs repeated-letter pattern analysis
- Allows iterative substitution of ciphertext letters
- Displays partial plaintext after each substitution
- Recovers the substitution key
- Displays the final recovered plaintext
- Verifies the solution by re-encryption

## Functions Used

The program contains the following main functions:

### `frequency_analysis()`

Counts the occurrence of each ciphertext letter, calculates its percentage frequency, and displays the letters in descending order of frequency.

### `word_frequency_analysis()`

Analyzes words in the ciphertext and identifies:

- One-letter words
- Two-letter words
- Three-letter words
- Repeated words

### `pattern_analysis()`

Determines the repeated-letter pattern of ciphertext words.

For example:

```text
QFR -> 012
QSS -> 011
RTRXET -> 010231
```

Letters having the same value in a pattern represent repeated letters.

For example:

```text
QSS -> 011
```

Here, the second and third letters are the same.

### `apply_substitution()`

Applies the currently recovered ciphertext-to-plaintext substitutions and generates a partial plaintext.

Unknown letters are represented using `_`.

### `display_partial_plaintext()`

Displays the partial plaintext after applying the currently known substitutions.

This helps determine whether a cryptanalytic hypothesis is correct.

### `verify_solution()`

Verifies the solution by encrypting the plaintext again and comparing the generated ciphertext with the original ciphertext.

## Encryption Key

The monoalphabetic substitution key used for encryption is:

```text
Plain  : ABCDEFGHIJKLMNOPQRSTUVWXYZ
Cipher : QWERTYUIOPASDFGHJKLZXCVBNM
```

Each plaintext letter is always replaced by the corresponding ciphertext letter.

For example:

```text
A -> Q
B -> W
C -> E
D -> R
E -> T
```

## Cryptanalysis

Cryptanalysis is performed iteratively.

The program first displays the results of frequency, word, and pattern analysis. Based on these observations, candidate substitutions can be proposed.

The input format is:

```text
ciphertext_letter plaintext_letter
```

For example:

```text
Q A
```

means:

```text
Ciphertext Q -> Plaintext A
```

After every valid substitution, the program displays the partial plaintext.

This process can be continued until meaningful plaintext is recovered.

To stop entering substitutions, enter:

```text
DONE
```

## Recovered Key

For the substitution key used in the program, the complete ciphertext-to-plaintext mapping is:

```text
Q -> A
W -> B
E -> C
R -> D
T -> E
Y -> F
U -> G
I -> H
O -> I
P -> J
A -> K
....
```

## Program Execution

Keep the files in the same directory:

```text
Assignment-5/
|
|-- main.cpp
|-- plaintext.txt
|-- README.md
```

Compile the program using:

```bash
g++ main.cpp -o main
```

Run it using:

```bash
./main
```

## Output

The program displays:

1. Generated ciphertext
2. Letter-frequency analysis
3. Most frequent ciphertext letters
4. One-letter words
5. Two-letter words
6. Three-letter words
7. Repeated words
8. Word patterns
9. Partial plaintext during cryptanalysis
10. Recovered plaintext
11. Recovered substitution key
12. Verification result

## Conclusion

The assignment demonstrates that although a monoalphabetic substitution cipher has a large key space, it preserves the statistical properties and word patterns of the plaintext.

Letter frequencies, repeated words, word lengths, and repeated-letter patterns can therefore be used to propose substitutions and gradually recover the original plaintext and substitution key.
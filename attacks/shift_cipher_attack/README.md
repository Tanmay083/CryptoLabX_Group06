# Shift Cipher Cryptanalysis

## Overview

This project implements cryptanalysis techniques for a Shift (Caesar) Cipher.

The Shift Cipher is a monoalphabetic substitution cipher where each letter in the plaintext is shifted by a fixed
key k in {0, 1,...25} modulo 26. Since the key space is small ( |K| = 26), brute-force decryption is trivial.
Automated cryptanalysis automates key identification using two statistical techniques:

Dictionary Scoring: Decrypts the ciphertext using all 26 possible keys and counts how many decrypted words match a reference English dictionary. The key producing the highest count of valid English words is selected.

Chi-Square Analysis: Measures the goodness-of-fit between observed letter frequency distributions in candidate plaintexts and expected English letter frequencies. 

The system supports:

1. Shift Cipher encryption and decryption
2. Brute-force dictionary attack
3. Chi-Square statistical cryptanalysis
4. Automated testing and comparison of both attacks

The objective is to recover the encryption key from ciphertext without being given the key.

## Project Structure

```text
shift_cipher_attack/
├── dictionary/
│   └── english_words.txt
├── screenshots/
│   └── execution_results.png
├── reports/
│   └── Assignment_4_Report.pdf
├── src/
│   ├── shift_cipher.py
│   ├── brute_force_dictionary.py
│   ├── chi_square_attack.py
│   └── main.py
└── README.md
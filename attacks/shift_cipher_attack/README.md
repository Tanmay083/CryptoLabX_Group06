# Shift Cipher Cryptanalysis

## Overview

This project implements cryptanalysis techniques for a Shift (Caesar) Cipher.

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
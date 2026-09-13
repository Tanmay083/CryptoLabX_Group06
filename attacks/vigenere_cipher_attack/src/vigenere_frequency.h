#ifndef VIGENERE_FREQUENCY_H
#define VIGENERE_FREQUENCY_H

#include <string>
#include <vector>

struct FrequencyEntry {
    char letter;
    int count;
    double percentage;
};

std::vector<std::vector<FrequencyEntry>> frequency_analysis(
    const std::string& ciphertext,
    int key_length
);

int find_shift(
    const std::vector<FrequencyEntry>& frequencies
);

std::string find_key(
    const std::string& ciphertext,
    int key_length
);

#endif
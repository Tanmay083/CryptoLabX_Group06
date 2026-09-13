#ifndef WORD_FREQUENCY_ANALYSIS_H
#define WORD_FREQUENCY_ANALYSIS_H

#include <string>
#include <vector>

struct WordFrequency {
    std::string word;
    int count;
};

std::vector<WordFrequency> word_frequency_analysis(const std::string& text);

#endif
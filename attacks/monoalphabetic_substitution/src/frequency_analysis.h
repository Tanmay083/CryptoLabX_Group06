#ifndef FREQUENCY_ANALYSIS_H
#define FREQUENCY_ANALYSIS_H

#include <string>
#include <vector>

struct LetterFrequency {
    char letter;
    int count;
    double percentage;
};

std::vector<LetterFrequency> frequency_analysis(const std::string& text);

#endif
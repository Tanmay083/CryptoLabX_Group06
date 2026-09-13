#ifndef IC_ANALYSIS_H
#define IC_ANALYSIS_H

#include <string>
#include <vector>

double calculate_ic(const std::string& text);

std::vector<double> calculate_ic_for_key_lengths(
    const std::string& ciphertext,
    int max_key_length = 20
);

#endif
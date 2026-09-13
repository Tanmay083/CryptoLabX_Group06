#ifndef KASISKI_ANALYSIS_H
#define KASISKI_ANALYSIS_H

#include <string>
#include <vector>

std::string clean_ciphertext(const std::string& ciphertext);

std::vector<std::string> find_repeated_patterns(
    const std::string& ciphertext,
    int min_length = 3
);

std::vector<int> calculate_distances(
    const std::string& ciphertext,
    const std::string& pattern
);

std::vector<int> find_factors(int distance);

std::vector<int> kasiski_analysis(
    const std::string& ciphertext
);

#endif
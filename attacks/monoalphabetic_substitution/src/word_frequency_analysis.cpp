#include "word_frequency_analysis.h"

#include <algorithm>
#include <cctype>
#include <map>

std::vector<WordFrequency> word_frequency_analysis(const std::string& text) {
    std::map<std::string, int> word_counts;

    std::string current_word;

    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            current_word += static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );
        } else {
            if (!current_word.empty()) {
                word_counts[current_word]++;
                current_word.clear();
            }
        }
    }

    // Handle the final word if the text does not end with punctuation/space.
    if (!current_word.empty()) {
        word_counts[current_word]++;
    }

    std::vector<WordFrequency> frequencies;

    for (const auto& entry : word_counts) {
        frequencies.push_back({entry.first, entry.second});
    }

    // Sort by descending frequency, then alphabetically for ties.
    std::sort(
        frequencies.begin(),
        frequencies.end(),
        [](const WordFrequency& a, const WordFrequency& b) {
            if (a.count != b.count) {
                return a.count > b.count;
            }

            return a.word < b.word;
        }
    );

    return frequencies;
}
#include "frequency_analysis.h"

#include <algorithm>
#include <cctype>

std::vector<LetterFrequency> frequency_analysis(const std::string& text) {
    int counts[26] = {0};
    int total_letters = 0;

    // Count alphabetic characters
    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            char upper = static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );

            counts[upper - 'A']++;
            total_letters++;
        }
    }

    std::vector<LetterFrequency> frequencies;

    // Calculate count and percentage for A-Z
    for (int i = 0; i < 26; i++) {
        LetterFrequency entry;

        entry.letter = static_cast<char>('A' + i);
        entry.count = counts[i];

        if (total_letters > 0) {
            entry.percentage =
                (static_cast<double>(counts[i]) / total_letters) * 100.0;
        } else {
            entry.percentage = 0.0;
        }

        frequencies.push_back(entry);
    }

    // Sort in descending order of frequency
    std::sort(
        frequencies.begin(),
        frequencies.end(),
        [](const LetterFrequency& a, const LetterFrequency& b) {
            if (a.count != b.count) {
                return a.count > b.count;
            }

            return a.letter < b.letter;
        }
    );

    return frequencies;
}
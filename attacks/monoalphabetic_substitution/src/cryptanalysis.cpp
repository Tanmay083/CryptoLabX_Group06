#include "cryptanalysis.h"

#include "frequency_analysis.h"
#include "word_frequency_analysis.h"
#include "pattern_analysis.h"
#include "display_partial_plaintext.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<char, char> cryptanalysis(
    const std::string& ciphertext
) {
    std::map<char, char> substitution;

    // Step 1: Perform letter-frequency analysis.
    std::vector<LetterFrequency> letter_frequencies =
        frequency_analysis(ciphertext);

    std::cout << "\n=== Letter Frequency Analysis ===\n";

    for (const auto& entry : letter_frequencies) {
        if (entry.count > 0) {
            std::cout << entry.letter
                      << " : "
                      << entry.count
                      << " : "
                      << entry.percentage
                      << "%\n";
        }
    }

    // Step 2: Perform word-frequency analysis.
    std::vector<WordFrequency> word_frequencies =
        word_frequency_analysis(ciphertext);

    std::cout << "\n=== Word Frequency Analysis ===\n";

    for (const auto& entry : word_frequencies) {
        std::cout << entry.word
                  << " : "
                  << entry.count
                  << "\n";
    }

    // Step 3: Perform repeated-letter pattern analysis.
    std::vector<PatternInfo> patterns =
        pattern_analysis(ciphertext);

    std::cout << "\n=== Pattern Analysis ===\n";

    for (const auto& entry : patterns) {
        std::cout << entry.word
                  << " : "
                  << entry.pattern
                  << "\n";
    }

    // Substitutions will be added after examining the ciphertext.
    std::cout << "\n=== Partial Plaintext ===\n";
    display_partial_plaintext(ciphertext, substitution);

    return substitution;
}
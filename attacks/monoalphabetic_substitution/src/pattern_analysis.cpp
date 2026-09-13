#include "pattern_analysis.h"

#include <cctype>
#include <map>
#include <sstream>

std::string get_pattern(const std::string& word) {
    std::map<char, int> mapping;
    int next_number = 0;

    std::string pattern;

    for (char ch : word) {
        if (mapping.find(ch) == mapping.end()) {
            mapping[ch] = next_number++;
        }

        pattern += std::to_string(mapping[ch]);

        if (ch != word.back()) {
            pattern += ".";
        }
    }

    return pattern;
}

std::vector<PatternInfo> pattern_analysis(const std::string& text) {
    std::vector<PatternInfo> patterns;

    std::string current_word;

    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            current_word += static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );
        } else {
            if (!current_word.empty()) {
                patterns.push_back({
                    current_word,
                    get_pattern(current_word)
                });

                current_word.clear();
            }
        }
    }

    if (!current_word.empty()) {
        patterns.push_back({
            current_word,
            get_pattern(current_word)
        });
    }

    return patterns;
}
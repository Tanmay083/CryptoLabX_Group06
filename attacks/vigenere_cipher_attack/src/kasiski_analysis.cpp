#include "kasiski_analysis.h"

#include <algorithm>
#include <cctype>
#include <map>

std::string clean_ciphertext(const std::string& ciphertext) {
    std::string cleaned;

    for (char ch : ciphertext) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            cleaned += static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );
        }
    }

    return cleaned;
}

std::vector<std::string> find_repeated_patterns(
    const std::string& ciphertext,
    int min_length
) {
    std::vector<std::string> patterns;

    std::string text = clean_ciphertext(ciphertext);

    for (int length = min_length; length <= 5; length++) {
        std::map<std::string, int> occurrences;

        for (int i = 0; i + length <= static_cast<int>(text.size()); i++) {
            std::string pattern = text.substr(i, length);
            occurrences[pattern]++;
        }

        for (const auto& entry : occurrences) {
            if (entry.second >= 2) {
                patterns.push_back(entry.first);
            }
        }
    }

    return patterns;
}

std::vector<int> calculate_distances(
    const std::string& ciphertext,
    const std::string& pattern
) {
    std::vector<int> positions;
    std::vector<int> distances;

    std::string text = clean_ciphertext(ciphertext);

    size_t position = text.find(pattern);

    while (position != std::string::npos) {
        positions.push_back(static_cast<int>(position));
        position = text.find(pattern, position + 1);
    }

    for (size_t i = 1; i < positions.size(); i++) {
        distances.push_back(positions[i] - positions[i - 1]);
    }

    return distances;
}

std::vector<int> find_factors(int distance) {
    std::vector<int> factors;

    for (int i = 2; i <= distance; i++) {
        if (distance % i == 0) {
            factors.push_back(i);
        }
    }

    return factors;
}

std::vector<int> kasiski_analysis(
    const std::string& ciphertext
) {
    std::map<int, int> factor_counts;

    std::vector<std::string> patterns =
        find_repeated_patterns(ciphertext);

    for (const std::string& pattern : patterns) {
        std::vector<int> distances =
            calculate_distances(ciphertext, pattern);

        for (int distance : distances) {
            std::vector<int> factors =
                find_factors(distance);

            for (int factor : factors) {
                if (factor <= 20) {
                    factor_counts[factor]++;
                }
            }
        }
    }

    std::vector<std::pair<int, int>> ranked_factors(
        factor_counts.begin(),
        factor_counts.end()
    );

    std::sort(
        ranked_factors.begin(),
        ranked_factors.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }

            return a.first < b.first;
        }
    );

    std::vector<int> candidates;

    for (const auto& entry : ranked_factors) {
        candidates.push_back(entry.first);
    }

    return candidates;
}
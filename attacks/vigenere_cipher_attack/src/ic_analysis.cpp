#include "ic_analysis.h"

#include <cctype>
#include <vector>

double calculate_ic(const std::string& text) {
    int counts[26] = {0};
    int total = 0;

    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            char upper = static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );

            counts[upper - 'A']++;
            total++;
        }
    }

    if (total <= 1) {
        return 0.0;
    }

    long long numerator = 0;

    for (int count : counts) {
        numerator += static_cast<long long>(count) * (count - 1);
    }

    return static_cast<double>(numerator) /
           (static_cast<double>(total) * (total - 1));
}

std::vector<double> calculate_ic_for_key_lengths(
    const std::string& ciphertext,
    int max_key_length
) {
    std::vector<double> results;

    std::string cleaned;

    for (char ch : ciphertext) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            cleaned += static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );
        }
    }

    for (int key_length = 1;
         key_length <= max_key_length;
         key_length++) {

        double total_ic = 0.0;
        int groups = 0;

        for (int offset = 0;
             offset < key_length;
             offset++) {

            std::string group;

            for (int i = offset;
                 i < static_cast<int>(cleaned.size());
                 i += key_length) {
                group += cleaned[i];
            }

            if (group.size() > 1) {
                total_ic += calculate_ic(group);
                groups++;
            }
        }

        if (groups > 0) {
            results.push_back(total_ic / groups);
        } else {
            results.push_back(0.0);
        }
    }

    return results;
}
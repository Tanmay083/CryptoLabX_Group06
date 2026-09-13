#include "apply_substitution.h"

#include <cctype>

std::string apply_substitution(
    const std::string& text,
    const std::map<char, char>& substitution
) {
    std::string result;

    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            char upper = static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );

            auto it = substitution.find(upper);

            if (it != substitution.end()) {
                result += it->second;
            } else {
                result += upper;
            }
        } else {
            result += ch;
        }
    }

    return result;
}
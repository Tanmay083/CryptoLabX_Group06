#include "display_partial_plaintext.h"
#include "apply_substitution.h"

#include <iostream>

void display_partial_plaintext(
    const std::string& ciphertext,
    const std::map<char, char>& substitution
) {
    std::string partial_text =
        apply_substitution(ciphertext, substitution);

    std::cout << "\nPartial Plaintext:\n";
    std::cout << partial_text << "\n";
}
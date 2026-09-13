#ifndef DISPLAY_PARTIAL_PLAINTEXT_H
#define DISPLAY_PARTIAL_PLAINTEXT_H

#include <string>
#include <map>

void display_partial_plaintext(
    const std::string& ciphertext,
    const std::map<char, char>& substitution
);

#endif
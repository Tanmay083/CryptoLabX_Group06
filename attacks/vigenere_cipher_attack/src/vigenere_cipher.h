#ifndef VIGENERE_CIPHER_H
#define VIGENERE_CIPHER_H

#include <string>

std::string split_into_groups(
    const std::string& ciphertext,
    int key_length,
    int group_index
);

std::string vigenere_decrypt(
    const std::string& ciphertext,
    const std::string& key
);

std::string vigenere_encrypt(
    const std::string& plaintext,
    const std::string& key
);

bool verify(
    const std::string& plaintext,
    const std::string& ciphertext,
    const std::string& key
);

#endif
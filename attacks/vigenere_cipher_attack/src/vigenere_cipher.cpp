#include "vigenere_cipher.h"

#include <cctype>

std::string split_into_groups(
    const std::string& ciphertext,
    int key_length,
    int group_index
) {
    std::string group;

    for (int i = group_index;
         i < static_cast<int>(ciphertext.size());
         i += key_length) {
        group += ciphertext[i];
    }

    return group;
}

std::string vigenere_decrypt(
    const std::string& ciphertext,
    const std::string& key
) {
    std::string plaintext;
    int key_index = 0;

    for (char ch : ciphertext) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            char cipher =
                static_cast<char>(
                    std::toupper(static_cast<unsigned char>(ch))
                );

            int cipher_value = cipher - 'A';
            int key_value = key[key_index % key.size()] - 'A';

            char plain =
                static_cast<char>(
                    'A' + (cipher_value - key_value + 26) % 26
                );

            plaintext += plain;
            key_index++;
        } else {
            plaintext += ch;
        }
    }

    return plaintext;
}

std::string vigenere_encrypt(
    const std::string& plaintext,
    const std::string& key
) {
    std::string ciphertext;
    int key_index = 0;

    for (char ch : plaintext) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            char plain =
                static_cast<char>(
                    std::toupper(static_cast<unsigned char>(ch))
                );

            int plain_value = plain - 'A';
            int key_value = key[key_index % key.size()] - 'A';

            char cipher =
                static_cast<char>(
                    'A' + (plain_value + key_value) % 26
                );

            ciphertext += cipher;
            key_index++;
        } else {
            ciphertext += ch;
        }
    }

    return ciphertext;
}

bool verify(
    const std::string& plaintext,
    const std::string& ciphertext,
    const std::string& key
) {
    return vigenere_encrypt(plaintext, key) == ciphertext;
}
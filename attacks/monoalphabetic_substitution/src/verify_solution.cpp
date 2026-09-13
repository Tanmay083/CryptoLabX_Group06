#include "verify_solution.h"
#include "apply_substitution.h"

bool verify_solution(
    const std::string& plaintext,
    const std::string& ciphertext,
    const std::map<char, char>& encryption_key
) {
    std::string regenerated_ciphertext =
        apply_substitution(plaintext, encryption_key);

    return regenerated_ciphertext == ciphertext;
}
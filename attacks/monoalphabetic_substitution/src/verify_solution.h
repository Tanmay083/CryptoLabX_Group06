#ifndef VERIFY_SOLUTION_H
#define VERIFY_SOLUTION_H

#include <string>
#include <map>

bool verify_solution(
    const std::string& plaintext,
    const std::string& ciphertext,
    const std::map<char, char>& encryption_key
);

#endif
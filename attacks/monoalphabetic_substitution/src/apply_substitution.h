#ifndef APPLY_SUBSTITUTION_H
#define APPLY_SUBSTITUTION_H

#include <string>
#include <map>

std::string apply_substitution(
    const std::string& text,
    const std::map<char, char>& substitution
);

#endif
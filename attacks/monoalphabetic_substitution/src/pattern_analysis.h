#ifndef PATTERN_ANALYSIS_H
#define PATTERN_ANALYSIS_H

#include <string>
#include <vector>

struct PatternInfo {
    std::string word;
    std::string pattern;
};

std::vector<PatternInfo> pattern_analysis(const std::string& text);

#endif
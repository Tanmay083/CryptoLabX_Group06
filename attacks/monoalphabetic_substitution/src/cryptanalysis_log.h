#ifndef CRYPTANALYSIS_LOG_H
#define CRYPTANALYSIS_LOG_H

#include <string>

struct CryptanalysisStep {
    int step;
    std::string observation;
    std::string possible_substitution;
    std::string substitution_tested;
    std::string result;
    std::string decision;
};

#endif
#include "ConvertScoreToString.h"

std::string convertScoreToString(double score) {
    std::string result = std::to_string(score);

    while (result.back() == '0') {
        result.pop_back();
    }

    if (result.back() == '.') {
        result.pop_back();
    }

    return result;
}

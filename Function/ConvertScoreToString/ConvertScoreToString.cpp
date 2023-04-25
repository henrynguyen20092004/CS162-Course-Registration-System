#include "ConvertScoreToString.h"

std::string convertScoreToString(double score) {
    std::string result = std::to_string(score);

    while (result.back() == '0' || result.back() == '.') {
        result.pop_back();
    }

    return result;
}

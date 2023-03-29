#include "ValidatePath.h"

void validatePath(const std::string &path) {
    if (path == "") {
        throw std::invalid_argument("Please enter a path!\n");
    }

    int length = path.length();
    std::string invalidChar = ":*?\"<>|";

    for (int i = 0; i < length; i++) {
        if ((path[i] == '/' && path[i + 1] == '/') ||
            invalidChar.find(path[i]) != std::string::npos) {
            throw std::invalid_argument("Please enter a valid path!\n");
        }
    }
}

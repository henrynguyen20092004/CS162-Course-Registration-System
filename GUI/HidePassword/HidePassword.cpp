#include "HidePassword.h"

#include <cstring>

void hidePassword(char *inputtedPassword, char *savedPassword) {
    int inputtedLength = strlen(inputtedPassword), savedLength = strlen(savedPassword);

    if (inputtedLength > savedLength) {
        savedPassword[savedLength] = inputtedPassword[inputtedLength - 1];
        savedPassword[savedLength + 1] = '\0';
        inputtedPassword[inputtedLength - 1] = '*';
    } else if (inputtedLength < savedLength) {
        savedPassword[savedLength - 1] = '\0';
    }
}

#include "InputPassword.h"

#include <conio.h>

std::string inputPassword(const std::string &prompt) {
    std::string password;
    char passChar;
    std::cout << prompt;

    do {
        passChar = getch();
        if (passChar == '\b') {
            int currentPasswordLength = password.length();

            if (currentPasswordLength != 0) {
                password.erase(--currentPasswordLength);
            }
        } else if (passChar != '\r') {
            password += passChar;
        }
    } while (passChar != '\r');

    std::cout << '\n';
    return password;
}

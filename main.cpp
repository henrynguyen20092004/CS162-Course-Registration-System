#include "Function/Function.h"

int main() {
    try {
        User currentUser = logIn();
        std::cout << "Welcome, " << currentUser.username << '\n';
    } catch (std::exception &error) {
        std::cout << error.what();
    }

    system("pause");
    return 0;
}

#include "Function/Function.h"

int main() {
    try {
        User currentUser = logIn();
        std::cout << "Welcome, " << currentUser.username << '\n';
        std::cout << "This is a test to the change password function\n";
        changePassword(currentUser);
    } catch (std::exception &error) {
        std::cout << error.what();
    }

    system("pause");
    return 0;
}

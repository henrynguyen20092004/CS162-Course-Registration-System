#include "Function/Function.h"

int main() {
    User currentUser = logIn();
    std::cout << "Welcome, " << currentUser.username << '\n';
    system("pause");
    processCommand(STOP);
}

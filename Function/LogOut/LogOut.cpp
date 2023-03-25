#include "LogOut.h"

void logOut(User &currentUser) {
    currentUser.username = "";
    currentUser.password = "";
    std::cout << "Successfully logged out!\n";
}

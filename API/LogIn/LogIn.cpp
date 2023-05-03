#include "LogIn.h"

#include "../../GlobalVar/GlobalVar.h"

bool checkUserExists(Node<User> *allUsers, const User &user) {
    for (; allUsers; allUsers = allUsers->next) {
        User currentUser = allUsers->data;

        if (user.username == currentUser.username &&
            user.password == currentUser.password) {
            return true;
        }
    }

    return false;
}

void logIn(char **inputs) {
    GlobalVar::currentUser.username = inputs[0];
    GlobalVar::currentUser.password = inputs[2];

    if (!checkUserExists(GlobalVar::allData.allUsers, GlobalVar::currentUser)) {
        throw std::invalid_argument("Invalid credentials, please try again!");
    }
}

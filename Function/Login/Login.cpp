#include "LogIn.h"

#include "../../Struct/Data.h"

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

User logIn(char **inputs) {
    User user;
    user.username = inputs[0];
    user.password = inputs[1];

    if (!checkUserExists(allData.allUsers, user)) {
        throw std::invalid_argument("Invalid credentials, please try again!");
    }

    return user;
}

#include "ChangePassword.h"

#include <cstring>

#include "../../GlobalVar/GlobalVar.h"
#include "../Save/SaveUser/SaveUser.h"

void updateUser(Node<User> *allUsers, const User &newUser) {
    for (; allUsers; allUsers = allUsers->next) {
        if (allUsers->data.username == newUser.username) {
            allUsers->data = newUser;
            return;
        }
    }
}

void changePassword(User &currentUser, char **inputs) {
    if (strcmp(inputs[3], currentUser.password.c_str())) {
        throw std::invalid_argument("Wrong old password, please try again!");
    }

    if (strcmp(inputs[4], inputs[5])) {
        throw std::invalid_argument("New password mismatch, please try again!");
    }

    currentUser.password = inputs[4];
    updateUser(GlobalVar::allData.allUsers, currentUser);
    saveAllUsers(GlobalVar::allData.allUsers);
}

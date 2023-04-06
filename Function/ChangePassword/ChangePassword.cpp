#include "ChangePassword.h"

#include "../../Struct/Data.h"
#include "../GetAll/GetAllUsers/GetAllUsers.h"
#include "../Input/Input.h"
#include "../Save/SaveUser/SaveUser.h"

void updateUser(Node<User> *allUsers, const User &newUser) {
    for (; allUsers; allUsers = allUsers->next) {
        if (allUsers->data.username == newUser.username) {
            allUsers->data = newUser;
            return;
        }
    }
}

void changePassword(User &currentUser) {
    std::string oldPassword, newPassword, confirmNewPassword;

    do {
        oldPassword = passwordInput("Please enter your old password: ");
        if (oldPassword != currentUser.password) {
            std::cout << "Wrong password, please enter again!\n";
        }
    } while (oldPassword != currentUser.password);

    do {
        newPassword = passwordInput("Please enter your new password: ");
        confirmNewPassword = passwordInput("Please confirm your new password: ");
        if (newPassword != confirmNewPassword) {
            std::cout << "Password mismatch, please enter again!\n";
        }
    } while (newPassword != confirmNewPassword);

    currentUser.password = newPassword;
    updateUser(allData.allUsers, currentUser);
    saveAllUsers(allData.allUsers);
    std::cout << "Password successfully changed!\n";
}

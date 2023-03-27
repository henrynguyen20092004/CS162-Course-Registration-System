#include "ChangePassword.h"

#include "../GetAll/GetAllUsers/GetAllUsers.h"
#include "../Input/Input.h"

void updateUser(Node<User> *allUsers, const User &newUser) {
    for (; allUsers; allUsers = allUsers->next) {
        if (allUsers->data.username == newUser.username) {
            allUsers->data = newUser;
            return;
        }
    }
}

void saveAllUsers(Node<User> *allUsers) {
    std::ofstream fout;
    writeFile(fout, "Data/User.txt");

    for (; allUsers; allUsers = allUsers->next) {
        fout << allUsers->data.username << '\n';
        fout << allUsers->data.password << '\n';
    }
}

void changePassword(User &currentUser) {
    std::string oldPassword, newPassword, confirmNewPassword;
    Node<User> *allUsers = getAllUsers();

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
    updateUser(allUsers, currentUser);
    saveAllUsers(allUsers);
    std::cout << "Password successfully changed!\n";
}

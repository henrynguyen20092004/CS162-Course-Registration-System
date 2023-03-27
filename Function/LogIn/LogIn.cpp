#include "LogIn.h"

#include "../GetAll/GetAllUsers/GetAllUsers.h"
#include "../Input/Input.h"

bool userExists(Node<User> *allUsers, const User &user) {
    for (; allUsers; allUsers = allUsers->next) {
        User currentUser = allUsers->data;

        if (user.username == currentUser.username &&
            user.password == currentUser.password) {
            return true;
        }
    }

    return false;
}

User logIn() {
    Node<User> *allUsers = getAllUsers();
    User user;
    bool found;

    do {
        std::cout << "Please enter your username: ";
        getline(std::cin, user.username);
        user.password = passwordInput("Please enter your password: ");
        found = userExists(allUsers, user);

        if (!found) {
            std::cout << "Invalid credentials, please try again!\n";
        }
    } while (!found);

    std::cout << "Welcome, " << user.username << '\n';
    deleteLinkedList(allUsers);
    return user;
}

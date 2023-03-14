#include "LogIn.h"

#include "../../Struct/LinkedList.h"
#include "../../Struct/User.h"
#include "../GetAllUsers/GetAllUsers.h"
#include "../InputPassword/InputPassword.h"

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
        user.password = inputPassword("Please enter your password: ");
        found = userExists(allUsers, user);

        if (!found) {
            std::cout << "Invalid credentials, please enter again!\n";
        }
    } while (!found);

    deleteLinkedList(allUsers);
    return user;
}

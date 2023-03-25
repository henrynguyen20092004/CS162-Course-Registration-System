#include "GetAllUsers.h"

#include "../OpenFile/OpenFile.h"

Node<User> *getAllUsers() {
    std::ifstream fin;
    readFile(fin, "Data/User.txt");
    User user;
    Node<User> *result = nullptr, *cur;

    while (fin.good()) {
        getline(fin, user.username);
        getline(fin, user.password);

        if (user.username == "") {
            break;
        }

        Node<User> *newNode = new Node<User>(user);

        if (result) {
            cur->next = newNode;
            cur = cur->next;
        } else {
            result = newNode;
            cur = result;
        }
    }

    fin.close();
    return result;
}

#include "GetAllUsers.h"

#include "../OpenFile/OpenFile.h"

Node<User> *getAllUsers() {
    std::ifstream fin;
    readFile(fin, "Data/User.txt");
    User user;
    Node<User> *result = nullptr, *cur = nullptr;

    while (fin.good()) {
        getline(fin, user.username);
        getline(fin, user.password);

        if (user.username == "") {
            break;
        }

        result = new Node<User>(user, cur);
        cur = result;
    }

    fin.close();
    return result;
}

#include "GetAllUsers.h"

#include <fstream>

Node<User> *getAllUsers() {
    Node<User> *result = nullptr;
    std::ifstream fin;
    fin.open("Data/User.txt");

    if (!fin.is_open()) {
        std::cout << "Can't open User.txt, please check if the file exists!\n";
    } else {
        User user;
        Node<User> *cur = nullptr;

        while (!fin.eof()) {
            getline(fin, user.username);
            getline(fin, user.password);

            result = new Node<User>(user, cur);
            cur = result;
        }

        fin.close();
    }

    return result;
}

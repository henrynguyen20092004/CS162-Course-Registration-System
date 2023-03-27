#include "GetAllUsers.h"

void readUser(std::ifstream &fin, User &user) {
    getline(fin, user.username);
    getline(fin, user.password);
}

Node<User> *getAllUsers() { 
    return getAll("Data/User.txt", &readUser);
}

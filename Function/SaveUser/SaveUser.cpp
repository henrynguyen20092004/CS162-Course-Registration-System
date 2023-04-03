#include "SaveUser.h"

#include "../OpenFile/OpenFile.h"

void saveAllUsers(Node<User> *allUsers) {
    std::ofstream fout;
    writeFile(fout, "Data/User.txt");

    for (; allUsers; allUsers = allUsers->next) {
        User user = allUsers->data;
        fout << user.username << '\n';
        fout << user.password << '\n';
    }
}

#include "CreateStudentAccount.h"

std::string createPassword(const std::string &dateOfBirth) {
    std::string passWord;
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        passWord += dateOfBirth[i];
    }
    return passWord;
}

User createAccount(const Student &student) {
    User studentAccount;
    studentAccount.username = student.id;
    studentAccount.password = createPassword(student.dateOfBirth);
    return studentAccount;
}

void saveAccount(const Student &student) {
    User studentAccount = createAccount(student);
    std::ofstream fout;
    writeFile(fout, "Data/User.txt", std::ios::app);
    fout << studentAccount.username << '\n';
    fout << studentAccount.password << '\n';
    fout << '\n';

    fout.close();
}

void createStudentAccount(const Student &student) {
    createAccount(student);
    saveAccount(student);
}

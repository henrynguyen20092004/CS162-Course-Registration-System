#include "CreateStudentAccount.h"

#include "../../OpenFile/OpenFile.h"

std::string getPasswordFromDateOfBirth(const std::string &dateOfBirth) {
    return dateOfBirth.substr(0, 2) + dateOfBirth.substr(3, 2) + dateOfBirth.substr(6);
}

User createAccount(const Student &student) {
    User studentAccount;
    studentAccount.username = student.id;
    studentAccount.password = getPasswordFromDateOfBirth(student.dateOfBirth);
    return studentAccount;
}

void saveAccount(const User &studentAccount) {
    std::ofstream fout;
    writeFile(fout, "Data/User.txt", std::ios::app);
    fout << studentAccount.username << '\n';
    fout << studentAccount.password << '\n';
    fout.close();
}

void createStudentAccount(const Student &student) {
    User studentAccount = createAccount(student);
    saveAccount(studentAccount);
}

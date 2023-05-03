#include "CreateStudentAccount.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../OpenFile/OpenFile.h"
#include "../../PasswordFunction/PasswordFunction.h"

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
    addNewItemsToOldList(GlobalVar::allData.allUsers, new Node(studentAccount));
}

void createStudentAccount(const Student &student) {
    User studentAccount = createAccount(student);
    saveAccount(studentAccount);
}

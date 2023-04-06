#include "UpdateDefaultStudentPassword.h"

#include "../../Create/CreateStudentAccount/CreateStudentAccount.h"

void updateDefaultStudentPassword(
    Node<Student> *curStudent, Node<User> *allUsers, const Student &student
) {
    if (curStudent->data.dateOfBirth != student.dateOfBirth) {
        for (; allUsers; allUsers = allUsers->next) {
            if (allUsers->data.password ==
                getPasswordFromDateOfBirth(curStudent->data.dateOfBirth)) {
                allUsers->data.password = getPasswordFromDateOfBirth(student.dateOfBirth);
                return;
            }
        }
    }
}

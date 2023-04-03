#include "UpdateDefaultStudentPassword.h"

#include "../../Create/CreateStudentAccount/CreateStudentAccount.h"

void updateDefaultStudentPassword(
    Node<Student> *allStudents, Node<User> *allUsers, const Student &student
) {
    if (allStudents->data.dateOfBirth != student.dateOfBirth) {
        for (; allUsers; allUsers = allUsers->next) {
            if (allUsers->data.password ==
                getPasswordFromDateOfBirth(allStudents->data.dateOfBirth)) {
                allUsers->data.password = getPasswordFromDateOfBirth(student.dateOfBirth);
                return;
            }
        }
    }
}

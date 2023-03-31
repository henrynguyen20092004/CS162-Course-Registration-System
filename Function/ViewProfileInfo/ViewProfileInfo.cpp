#include "ViewProfileInfo.h"

#include "../DisplayStudentInfo/DisplayStudentInfo.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"

void viewProfileInfo(const User &currentUser) {
    std::cout << "Your profile info:\n";

    if (currentUser.username == "admin") {
        std::cout << "- Name: admin\n";
        return;
    }

    Node<Student> *allStudents = getAllStudents(), *cur = allStudents;

    for (; cur; cur = cur->next) {
        Student student = cur->data;

        if (student.id == currentUser.username) {
            displayStudentInfo(student);
            break;
        }
    }

    deleteLinkedList(allStudents);
}

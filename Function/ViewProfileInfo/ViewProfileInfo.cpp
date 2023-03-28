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

    while (cur) {
        if (cur->data.id == currentUser.username) {
            displayStudentInfo(cur->data);
            break;
        }

        cur = cur->next;
    }

    deleteLinkedList(allStudents);
}

#include "ViewProfileInfo.h"

#include "../GetAll/GetAllStudents/GetAllStudents.h"

void displayStudentInfo(const Student &student) {
    std::cout << "- Student ID: " << student.id << '\n';
    std::cout << "- Name: " << student.lastName << ' ' << student.firstName << '\n';
    std::cout << "- Gender: " << student.gender << '\n';
    std::cout << "- Date of birth: " << student.dateOfBirth << '\n';
    std::cout << "- Social ID: " << student.socialID << '\n';
    std::cout << "- Class: " << student.className << '\n';
}

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

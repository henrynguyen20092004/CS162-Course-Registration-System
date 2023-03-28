#include "DisplayStudentInfo.h"

void displayStudentInfo(const Student &student) {
    std::cout << "- Student ID: " << student.id << '\n';
    std::cout << "- Name: " << student.lastName << ' ' << student.firstName << '\n';
    std::cout << "- Gender: " << student.gender << '\n';
    std::cout << "- Date of birth: " << student.dateOfBirth << '\n';
    std::cout << "- Social ID: " << student.socialID << '\n';
    std::cout << "- Class: " << student.className << '\n';
}

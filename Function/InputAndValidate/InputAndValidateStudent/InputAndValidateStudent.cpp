#include "InputAndValidateStudent.h"

#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckStudentID/CheckStudentID.h"
#include "../../DateFunction/DateFunction.h"
#include "../../Input/Input.h"

void inputStudent(Student &student) {
    std::cout << "Please fill the information in every box\n";
    std::cout << "Student ID: ";
    getline(std::cin, student.id);
    std::cout << "First name (only one word): ";
    student.firstName = nameInput();
    std::cout << "Last name: ";
    student.lastName = nameInput();
    std::cout << "Gender (M: Male, F: Female): ";
    getline(std::cin, student.gender);
    std::cout << "Date of birth (dd/mm/yyyy): ";
    getline(std::cin, student.dateOfBirth);
    std::cout << "Social ID: ";
    getline(std::cin, student.socialID);
    std::cout << "Class name: ";
    getline(std::cin, student.className);
}

void validateStudent(Node<std::string> *allClasses, Student &student) {
    if (student.gender == "M" || student.gender == "m") {
        student.gender = "M";
    } else if (student.gender == "F" || student.gender == "f") {
        student.gender = "F";
    } else {
        throw std::invalid_argument("Invalid gender, please try again!\n");
    }

    if (!checkDate(student.dateOfBirth) ||
        !compareDate(student.dateOfBirth, getToday())) {
        throw std::invalid_argument("Invalid date of birth, please try again!\n");
    }

    if (!checkClassExists(allClasses, student.className)) {
        throw std::invalid_argument("This class doesn't exists, please try again!\n");
    }
}

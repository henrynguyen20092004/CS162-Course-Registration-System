#include "ValidateStudent.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../DateFunction/DateFunction.h"

void validateStudent(
    Node<Student> *allStudents, Node<std::string> *allClasses, Student &student,
    bool checkStudentAlreadyExists
) {
    if (checkStudentIDExists(allStudents, student.id) == checkStudentAlreadyExists) {
        if (checkStudentAlreadyExists) {
            throw std::invalid_argument("This student already exists, please try again!\n"
            );
        } else {
            throw std::invalid_argument("This student ID is invalid, please try again!\n"
            );
        }
    }

    if (student.gender == "M" || student.gender == "m") {
        student.gender = "M";
    } else if (student.gender == "F" || student.gender == "f") {
        student.gender = "F";
    } else {
        throw std::invalid_argument("Invalid gender, please try again!\n");
    }

    if (!checkDate(student.dateOfBirth)) {
        throw std::invalid_argument("Invalid date of birth, please try again!\n");
    }

    if (!checkClassExists(allClasses, student.className)) {
        throw std::invalid_argument("This class doesn't exists, please try again!\n");
    }
}
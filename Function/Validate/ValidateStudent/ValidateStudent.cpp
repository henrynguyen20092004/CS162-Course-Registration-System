#include "ValidateStudent.h"

#include <stdexcept>

#include "../../Check/CheckClass/CheckClass.h"
#include "../../DateFunction/DateFunction.h"

void validateStudent(Node<std::string> *allClasses, Student &student) {
    if (student.gender == "M" || student.gender == "m") {
        student.gender = "M";
    } else if (student.gender == "F" || student.gender == "f") {
        student.gender = "F";
    } else {
        throw std::invalid_argument("Invalid gender, please try again!");
    }

    if (!checkDate(student.dateOfBirth) ||
        !compareDate(student.dateOfBirth, getToday())) {
        throw std::invalid_argument("Invalid date of birth, please try again!");
    }

    if (!checkClassExists(allClasses, student.className)) {
        throw std::invalid_argument("This class doesn't exists, please try again!");
    }
}

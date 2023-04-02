#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

struct Student {
    std::string id, firstName, lastName, gender, dateOfBirth, socialID, className;
};

inline bool operator==(const Student &firstStudent, const Student &secondStudent) {
    return firstStudent.id == secondStudent.id &&
           firstStudent.firstName == secondStudent.firstName &&
           firstStudent.lastName == secondStudent.lastName &&
           firstStudent.gender == secondStudent.gender &&
           firstStudent.dateOfBirth == secondStudent.dateOfBirth &&
           firstStudent.socialID == secondStudent.socialID &&
           firstStudent.className == secondStudent.className;
}

#endif

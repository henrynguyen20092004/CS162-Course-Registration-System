#include "CheckStudent.h"

bool checkStudentIDExists(Node<Student>* allStudents, const std::string& studentID) {
    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data.id == studentID) {
            return true;
        }
    }

    return false;
}

bool checkStudentInClass(
    Node<Student>* allStudentsInClass, const std::string& studentID
) {
    while (allStudentsInClass) {
        if (studentID == allStudentsInClass->data.id) {
            return true;
        }

        allStudentsInClass = allStudentsInClass->next;
    }

    return false;
}

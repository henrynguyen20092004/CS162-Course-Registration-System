#include "CheckStudentID.h"

#include "../GetAllStudents/GetAllStudents.h"

bool checkStudentIDExists(Node<Student>* allStudents, const std::string& studentID) {
    while (allStudents) {
        if (allStudents->data.id == studentID) {
            return true;
        }

        allStudents = allStudents->next;
    }

    return false;
}

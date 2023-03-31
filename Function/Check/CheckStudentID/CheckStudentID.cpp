#include "CheckStudentID.h"

bool checkStudentIDExists(Node<Student>* allStudents, const std::string& studentID) {
    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data.id == studentID) {
            return true;
        }
    }

    return false;
}

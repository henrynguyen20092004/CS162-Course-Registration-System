#include "CheckStudentID.h"

bool checkStudentIDExists(Node<Student>* allStudent, const std::string& studentID) {
    for (; allStudent; allStudent = allStudent->next) {
        if (allStudent->data.id == studentID) {
            return true;
        }
    }

    return false;
}

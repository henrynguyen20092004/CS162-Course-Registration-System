#include "CheckStudentID.h"

bool checkStudentID(const std::string &studentID) {
    Node<Student> *allStudents = getAllStudents();
    while (allStudents) {
        if (allStudents->data.id == studentID) {
            return true;
        }
        allStudents = allStudents->next;
    }
    return false;
}
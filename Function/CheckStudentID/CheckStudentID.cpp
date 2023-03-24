#include "CheckStudentID.h"

bool checkStudentIDExists(const std::string &studentID) {
    Node<Student> *allStudents = getAllStudents();

    while (allStudents) {
        if (allStudents->data.id == studentID) {
            return true;
        }

        allStudents = allStudents->next;
    }

    deleteLinkedList(allStudents);
    return false;
}

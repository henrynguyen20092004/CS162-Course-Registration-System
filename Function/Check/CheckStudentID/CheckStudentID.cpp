#include "CheckStudentID.h"

bool checkStudentIDExists(Node<Student>* allStudents, const std::string& studentID) {
    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data.id == studentID) {
            return true;
        }
    }

    return false;
}

bool isInClass(Node<Student>*& allStudentsInClass, const std::string& studentID) {
    Node<Student>* cur = allStudentsInClass;
    while (cur) {
        if (studentID == cur->data.id) {
            return true;
        }
        cur = cur->next;
    }
    deleteLinkedList(cur);
    return false;
}

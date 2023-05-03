#include "GetAllStudentsInClass.h"

#include "../../../GlobalVar/GlobalVar.h"

Node<Student> *getAllStudentsInClass(const std::string &className) {
    Node<Student> *allStudentsInClass = nullptr, *curStudentsInClass,
                  *curStudent = GlobalVar::allData.allStudents;

    for (; curStudent; curStudent = curStudent->next) {
        if (className == curStudent->data.className) {
            pushToEndOfLinkedList(
                allStudentsInClass, curStudentsInClass, curStudent->data
            );
        }
    }

    return allStudentsInClass;
}

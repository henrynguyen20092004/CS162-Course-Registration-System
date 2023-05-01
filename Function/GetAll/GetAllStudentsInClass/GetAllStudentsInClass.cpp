#include "GetAllStudentsInClass.h"

#include "../../../GlobalVar/GlobalVar.h"

Node<Student> *getAllStudentsInClass(const std::string &className) {
    Node<Student> *allClassStudents = nullptr, *curClassStudents,
                  *curStudent = GlobalVar::allData.allStudents;

    for (; curStudent; curStudent = curStudent->next) {
        if (className == curStudent->data.className) {
            pushToEndLinkedList(allClassStudents, curClassStudents, curStudent->data);
        }
    }

    return allClassStudents;
}

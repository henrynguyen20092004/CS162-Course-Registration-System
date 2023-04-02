#include "GetAllStudentsInClass.h"

#include "../../OpenFile/OpenFile.h"
#include "../GetAllStudents/GetAllStudents.h"

Node<Student> *getAllStudentsInClass(const std::string &className) {
    Node<Student> *allStudents = getAllStudents(), *cur = allStudents,
                  *allClassStudents = nullptr, *cur2;

    for (; cur; cur = cur->next) {
        if (className == cur->data.className) {
            pushToEndLinkedList(allClassStudents, cur2, cur->data);
        }
    }

    deleteLinkedList(allStudents);
    return allClassStudents;
}

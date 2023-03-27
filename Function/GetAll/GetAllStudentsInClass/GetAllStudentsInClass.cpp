#include "GetAllStudentsInClass.h"

#include "../GetAllStudents/GetAllStudents.h"
#include "../../OpenFile/OpenFile.h"

Node<Student> *getAllStudentsInClass(const std::string &className) {
    Node<Student> *allStudents = getAllStudents(), *cur = allStudents,
                  *allClassStudents = nullptr, *cur2;

    while (cur) {
        if (className == cur->data.className) {
            if (!allClassStudents) {
                allClassStudents = new Node<Student>(cur->data);
                cur2 = allClassStudents;
            } else {
                cur2->next = new Node<Student>(cur->data);
                cur2 = cur2->next;
            }
        }

        cur = cur->next;
    }

    deleteLinkedList(allStudents);
    return allClassStudents;
}

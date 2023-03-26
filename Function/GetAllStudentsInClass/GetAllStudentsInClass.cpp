#include "GetAllStudentsInClass.h"

#include "../../Struct/Student.h"
#include "../GetAllStudents/GetAllStudents.h"
#include "../OpenFile/OpenFile.h"

Node<std::string> *getAllStudentsInClass(const std::string &className) {
    Node<Student> *allStudents = getAllStudents(), *cur = allStudents;
    Node<std::string> *allClassStudents = nullptr, *cur2;

    while (cur) {
        if (className == cur->data.className) {
            if (!allClassStudents) {
                allClassStudents = new Node<std::string>(cur->data.id);
                cur2 = allClassStudents;
            } else {
                cur2->next = new Node<std::string>(cur->data.id);
                cur2 = cur2->next;
            }
        }

        cur = cur->next;
    }

    deleteLinkedList(allStudents);
    return allClassStudents;
}

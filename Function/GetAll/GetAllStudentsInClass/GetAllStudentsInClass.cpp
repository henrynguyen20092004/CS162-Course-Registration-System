#include "GetAllStudentsInClass.h"

#include "../../OpenFile/OpenFile.h"
#include "../GetAllStudents/GetAllStudents.h"

Node<Student> *getAllStudentsInClass(const std::string &className) {
    Node<Student> *allStudents = getAllStudents(), *cur = allStudents,
                  *allClassStudents = nullptr, *cur2;

    for (; cur; cur = cur->next) {
        if (className == cur->data.className) {
            Node<Student> *newNode = new Node(cur->data);

            if (!allClassStudents) {
                allClassStudents = newNode;
            } else {
                cur2->next = newNode;
            }

            cur2 = newNode;
        }
    }

    deleteLinkedList(allStudents);
    return allClassStudents;
}

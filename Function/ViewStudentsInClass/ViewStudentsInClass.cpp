#include "ViewStudentsInClass.h"

#include "../../Struct/LinkedList.h"
#include "../DisplayStudentInfo/DisplayStudentInfo.h"

void viewStudentsInClass() {
    std::string className;
    std::cout << "Enter the class you want to view students: ";
    getline(std::cin, className);
    Node<Student> *getAllStudents = getAllStudentsInClass(className);
    Node<Student> *cur = getAllStudents;
    while (cur) {
        displayStudentInfo(cur->data);
        cur = cur->next;
    }
    deleteLinkedList(getAllStudents);
}
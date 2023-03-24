#include "GetAllStudents.h"

#include "../OpenFile/OpenFile.h"

Node<Student> *getAllStudents() {
    std::ifstream fin;
    readFile(fin, "Data/Student.txt");
    Student student;
    Node<Student> *result = nullptr, *cur = nullptr;

    while (fin.good()) {
        getline(fin, student.id);

        if (student.id == "") {
            continue;
        }

        getline(fin, student.firstName);
        getline(fin, student.lastName);
        getline(fin, student.gender);
        getline(fin, student.dateOfBirth);
        getline(fin, student.socialID);
        getline(fin, student.className);

        Node<Student> *tmp = new Node(student);

        if (!result) {
            result = tmp;
            cur = result;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }

    fin.close();
    return result;
}

#include "GetAllStudentsInCourse.h"

#include "../../OpenFile/OpenFile.h"
#include "../GetAllStudents/GetAllStudents.h"

Node<Student> *getAllStudentsInCourse(const Course &course) {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student> *allStudents = getAllStudents(), *allStudentsInCourse = nullptr, *cur;
    std::string studentID, course_class;

    while (fin.good()) {
        getline(fin, studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, course_class);

        if (course.id == course_class.substr(0, course_class.find('-'))) {
            for (Node<Student> *cur2 = allStudents; cur2; cur2 = cur2->next) {
                if (cur2->data.id == studentID) {
                    Node<Student> *newNode = new Node(cur2->data);

                    if (!allStudentsInCourse) {
                        allStudentsInCourse = newNode;
                    } else {
                        cur->next = newNode;
                    }

                    cur = newNode;
                }
            }
        }
    }

    fin.close();
    deleteLinkedList(allStudents);
    return allStudentsInCourse;
}

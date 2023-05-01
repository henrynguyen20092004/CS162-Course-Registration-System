#include "GetAllStudentsInCourse.h"

#include "../../../GlobalVar/GlobalVar.h"

Node<Student> *getAllStudentsInCourse(const Course &course) {
    std::ifstream fin;
    readFile(fin, "Data/StudentCourse.txt");

    Node<Student> *allStudentsInCourse = nullptr, *curStudentsInCourse;
    std::string studentID, courseID, className;

    while (fin.good()) {
        getline(fin, studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, courseID);
        getline(fin, className);

        if (course.id == courseID && course.className == className) {
            for (Node<Student> *curStudent = GlobalVar::allData.allStudents; curStudent;
                 curStudent = curStudent->next) {
                if (curStudent->data.id == studentID) {
                    pushToEndLinkedList(
                        allStudentsInCourse, curStudentsInCourse, curStudent->data
                    );
                }
            }
        }
    }

    fin.close();
    return allStudentsInCourse;
}

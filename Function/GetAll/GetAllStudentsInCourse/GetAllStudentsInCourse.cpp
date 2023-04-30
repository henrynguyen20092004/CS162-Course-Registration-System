#include "GetAllStudentsInCourse.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../OpenFile/OpenFile.h"

Node<Student> *getAllStudentsInCourse(const Course &course) {
    std::ifstream fin;
    readFile(fin, "Data/StudentCourse.txt");

    Node<Student> *allStudentsInCourse = nullptr, *cur;
    std::string studentID, courseID, className;

    while (fin.good()) {
        getline(fin, studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, courseID);
        getline(fin, className);

        if (course.id == courseID && course.className == className) {
            for (Node<Student> *cur2 = GlobalVar::allData.allStudents; cur2;
                 cur2 = cur2->next) {
                if (cur2->data.id == studentID) {
                    pushToEndLinkedList(allStudentsInCourse, cur, cur2->data);
                }
            }
        }
    }

    fin.close();
    return allStudentsInCourse;
}

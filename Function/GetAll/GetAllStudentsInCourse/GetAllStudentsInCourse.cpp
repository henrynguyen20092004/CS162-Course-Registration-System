#include "GetAllStudentsInCourse.h"

#include "../../OpenFile/OpenFile.h"

Node<Student_Course> *getAllStudentsInCourse(const Course &course) {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student_Course> *allStudentsInCourse = nullptr, *cur = nullptr;
    Student_Course student_course;
    std::string tmpStudent_Course;

    while (fin.good()) {
        getline(fin, student_course.studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, student_course.courseID);
        tmpStudent_Course = student_course.courseID;

        student_course.courseID =
            tmpStudent_Course.substr(0, tmpStudent_Course.find('-'));
        student_course.className =
            tmpStudent_Course.substr(tmpStudent_Course.find('-') + 1);

        Node<Student_Course> *newNode = new Node(student_course);

        if (course.id == student_course.courseID) {
            if (!allStudentsInCourse) {
                allStudentsInCourse = newNode;
            } else {
                cur->next = newNode;
            }

            cur = newNode;
        }
    }

    fin.close();
    return allStudentsInCourse;
}

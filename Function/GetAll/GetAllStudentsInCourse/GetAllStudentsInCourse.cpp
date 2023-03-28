#include "GetAllStudentsInCourse.h"

#include "../../OpenFile/OpenFile.h"

Node<Student_Course> *getAllStudentsInCourse(const Course &course) {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student_Course> *allStudentsInCourse = nullptr, *cur = nullptr;
    Student_Course student_course;
    std::string course_class;

    while (fin.good()) {
        getline(fin, student_course.studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, course_class);
        student_course.courseID = course_class.substr(0, course_class.find('-'));
        student_course.className = course_class.substr(course_class.find('-') + 1);

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

#include "GetAllStudents.h"

#include "../OpenFile/OpenFile.h"

Node<Student> *getAllStudents() {
    std::ifstream fin;
    readFile(fin, "Data/Student.txt");
    Student student;
    Node<Student> *allStudents = nullptr, *cur = nullptr;

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

        if (!allStudents) {
            allStudents = tmp;
            cur = allStudents;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }

    fin.close();
    return allStudents;
}

Node<std::string> *getAllStudentsIDInClass(std::string &className) {
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allCourseStudents = nullptr;
    Node<std::string> *cur = allCourseStudents;

    while (allStudents) {
        if (className == allStudents->data.className) {
            if (!allCourseStudents) {
                allCourseStudents = new Node<std::string>(allStudents->data.id);
                cur = allCourseStudents;
            } else {
                cur->next = new Node<std::string>(allStudents->data.id);
                cur = cur->next;
            }
        }
        allStudents = allStudents->next;
    }

    deleteLinkedList(allStudents);
    return allCourseStudents;
}

Node<Student_Course> *getAllStudent_Course() {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student_Course> *allStudent_Course = nullptr;
    Node<Student_Course> *cur = nullptr;
    Student_Course student_course;

    while (fin.good()) {
        getline(fin, student_course.studentID);
        if (student_course.studentID == "") {
            break;
        }
        getline(fin, student_course.courseID);

        if (!allStudent_Course) {
            allStudent_Course = new Node<Student_Course>(student_course);
            cur = allStudent_Course;
        } else {
            cur->next = new Node<Student_Course>(student_course);
            cur = cur->next;
        }
    }

    fin.close();
    return allStudent_Course;
}

Node<Student_Course> *getAllStudentsInCourse(Course &course) {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student_Course> *allStudentsInCourse = nullptr;
    Node<Student_Course> *cur = nullptr;
    Student_Course student_course;

    while (fin.good()) {
        getline(fin, student_course.studentID);
        if (student_course.studentID == "") {
            break;
        }
        getline(fin, student_course.courseID);

        if (course.id == student_course.courseID) {
            if (!allStudentsInCourse) {
                allStudentsInCourse = new Node<Student_Course>(student_course);
                cur = allStudentsInCourse;
            } else {
                cur->next = new Node<Student_Course>(student_course);
                cur = cur->next;
            }
        }
    }

    fin.close();
    return allStudentsInCourse;
}

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

Node<Student_Course> *getAllStudent_Course() {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student_Course> *allStudent_Course = nullptr, *cur = nullptr, *tmp;
    Student_Course student_course;
    std::string course_class;

    while (fin.good()) {
        getline(fin, student_course.studentID);

        if (student_course.studentID == "") {
            break;
        }

        getline(fin, course_class);
        student_course.courseID = course_class.substr(0, course_class.find('-'));
        student_course.className = course_class.substr(course_class.find('-') + 1);

        tmp = new Node<Student_Course>(student_course);

        if (!allStudent_Course) {
            allStudent_Course = tmp;
            cur = allStudent_Course;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }

    fin.close();
    return allStudent_Course;
}

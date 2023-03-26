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
    Node<std::string> *allClassStudents = nullptr, *cur;

    while (allStudents) {
        if (className == allStudents->data.className) {
            if (!allClassStudents) {
                allClassStudents = new Node<std::string>(allStudents->data.id);
                cur = allClassStudents;
            } else {
                cur->next = new Node<std::string>(allStudents->data.id);
                cur = cur->next;
            }
        }
        allStudents = allStudents->next;
    }

    deleteLinkedList(allStudents);
    return allClassStudents;
}

Node<Student_Course_Class> *getAllStudent_Course_Class() {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course_Class.txt");

    Node<Student_Course_Class> *allStudent_Course_Class = nullptr, *cur;
    Student_Course_Class student_course_class;

    while (fin.good()) {
        getline(fin, student_course_class.studentID);
        if (student_course_class.studentID == "") {
            break;
        }
        getline(fin, student_course_class.courseID);

        student_course_class.className = student_course_class.courseID.substr(
            student_course_class.courseID.find('_') + 1
        );

        student_course_class.courseID = student_course_class.courseID.substr(
            0, student_course_class.courseID.find('_')
        );

        if (!allStudent_Course_Class) {
            allStudent_Course_Class =
                new Node<Student_Course_Class>(student_course_class);
            cur = allStudent_Course_Class;
        } else {
            cur->next = new Node<Student_Course_Class>(student_course_class);
            cur = cur->next;
        }
    }

    fin.close();
    return allStudent_Course_Class;
}

Node<Student_Course_Class> *getAllStudentsInCourse(Course &course) {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student_Course_Class> *allStudentsInCourse = nullptr, *cur;
    Student_Course_Class student_course_class;

    while (fin.good()) {
        getline(fin, student_course_class.studentID);
        if (student_course_class.studentID == "") {
            break;
        }
        getline(fin, student_course_class.courseID);

        student_course_class.className = student_course_class.courseID.substr(
            student_course_class.courseID.find('_') + 1
        );

        student_course_class.courseID = student_course_class.courseID.substr(
            0, student_course_class.courseID.find('_') + 1
        );

        if (course.id == student_course_class.courseID) {
            if (!allStudentsInCourse) {
                allStudentsInCourse =
                    new Node<Student_Course_Class>(student_course_class);
                cur = allStudentsInCourse;
            } else {
                cur->next = new Node<Student_Course_Class>(student_course_class);
                cur = cur->next;
            }
        }
    }

    fin.close();
    return allStudentsInCourse;
}

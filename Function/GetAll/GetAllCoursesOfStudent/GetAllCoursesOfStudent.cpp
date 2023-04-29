#include "GetAllCoursesOfStudent.h"

Node<StudentCourse> *getAllCoursesIDOfStudent(const std::string &studentID) {
    std::ifstream fin;
    readFile(fin, "Data/StudentCourse.txt");

    Node<StudentCourse> *allCoursesIDOfStudent = nullptr, *cur;
    StudentCourse studentCourse;

    while (fin.good()) {
        getline(fin, studentCourse.studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, studentCourse.courseID);
        getline(fin, studentCourse.className);

        if (studentCourse.studentID != studentID) {
            continue;
        }

        pushToEndLinkedList(allCoursesIDOfStudent, cur, studentCourse);
    }

    fin.close();
    return allCoursesIDOfStudent;
}

Node<Course> *getAllCoursesOfStudent(
    const std::string &studentID, const Semester &semester
) {
    if (semester.schoolYearName == "") {
        return nullptr;
    }

    Node<StudentCourse> *allCoursesIDOfStudent = getAllCoursesIDOfStudent(studentID);
    StudentCourse tmpStudentCourse;
    Course tmpCourse;
    Node<Course> *allCoursesOfStudent = nullptr, *curCourse;

    for (Node<StudentCourse> *cur1 = allCoursesIDOfStudent; cur1; cur1 = cur1->next) {
        tmpStudentCourse = cur1->data;

        for (Node<Course> *cur2 = allData.allCourses; cur2; cur2 = cur2->next) {
            tmpCourse = cur2->data;

            if (tmpCourse.id == tmpStudentCourse.courseID &&
                tmpCourse.className == tmpStudentCourse.className &&
                tmpCourse.schoolYearName == semester.schoolYearName &&
                tmpCourse.semesterNumber == semester.number) {
                pushToEndLinkedList(allCoursesOfStudent, curCourse, tmpCourse);
            }
        }
    }

    deleteLinkedList(allCoursesIDOfStudent);
    return allCoursesOfStudent;
}

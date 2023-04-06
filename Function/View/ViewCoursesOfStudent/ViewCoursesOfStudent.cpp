#include "ViewCoursesOfStudent.h"

#include "../../../Struct/Data.h"
#include "../ViewCourses/ViewCourses.h"

Node<StudentCourse> *getAllCoursesOfStudent(const std::string &studentID) {
    std::ifstream fin;
    readFile(fin, "Data/StudentCourse.txt");

    Node<StudentCourse> *allCoursesOfStudent = nullptr, *cur;
    StudentCourse studentCourse;
    std::string course_class;

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

        pushToEndLinkedList(allCoursesOfStudent, cur, studentCourse);
    }

    fin.close();
    return allCoursesOfStudent;
}

void viewCoursesOfStudent(const User &user, const Semester &semester) {
    if (semester.schoolYearName == "") {
        std::cout
            << "There's no semester at the moment, please change the current semester!\n";
        return;
    }

    Node<StudentCourse> *allCoursesOfStudent = getAllCoursesOfStudent(user.username);
    StudentCourse tmpStudentCourse;
    Course tmpCourse;
    bool haveCourses = false;
    int index = 0;

    for (Node<StudentCourse> *cur1 = allCoursesOfStudent; cur1; cur1 = cur1->next) {
        tmpStudentCourse = cur1->data;

        for (Node<Course> *cur2 = allData.allCourses; cur2; cur2 = cur2->next) {
            tmpCourse = cur2->data;

            if (tmpCourse.id == tmpStudentCourse.courseID &&
                tmpCourse.className == tmpStudentCourse.className &&
                tmpCourse.schoolYearName == semester.schoolYearName &&
                tmpCourse.semesterNumber == semester.number) {
                if (!haveCourses) {
                    std::cout << "This is the list of your courses:\n";
                    haveCourses = true;
                }

                std::cout << "This is course number " << ++index << ":\n";
                viewACourse(tmpCourse);
            }
        }
    }

    if (!haveCourses) {
        std::cout << "You have no courses at the moment!\n";
    }

    deleteLinkedList(allCoursesOfStudent);
}

#include "StudentViewCourses.h"

#include "../../Struct/Student_Course.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../ViewCourses/ViewCourses.h"

Node<Student_Course> *getAllCoursesOfStudent(const std::string &studentID) {
    std::ifstream fin;
    readFile(fin, "Data/Student_Course.txt");

    Node<Student_Course> *allCoursesOfStudent = nullptr, *cur;
    Student_Course student_course;
    std::string course_class;

    while (fin.good()) {
        getline(fin, student_course.studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, student_course.courseID);
        getline(fin, student_course.className);

        if (student_course.studentID != studentID) {
            continue;
        }

        pushToEndLinkedList(allCoursesOfStudent, cur, student_course);
    }

    fin.close();
    return allCoursesOfStudent;
}

void studentViewCourses(const User &user, const Semester &semester) {
    Node<Student_Course> *allCoursesOfStudent = getAllCoursesOfStudent(user.username);
    Node<Course> *allCourses = getAllCourses();
    Student_Course tmpStudentCourse;
    Course tmpCourse;
    bool haveCourses = false;
    int index = 0;

    for (Node<Student_Course> *cur1 = allCoursesOfStudent; cur1; cur1 = cur1->next) {
        tmpStudentCourse = cur1->data;

        for (Node<Course> *cur2 = allCourses; cur2; cur2 = cur2->next) {
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
    deleteLinkedList(allCourses);
}

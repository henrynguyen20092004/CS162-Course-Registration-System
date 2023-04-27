#include "GetAllCoursesOfSemester.h"

Node<Course>* getAllCourseOfSemester(
    const std::string& schoolYear, const int& semesterNumber
) {
    Node<Course>*allCourseOfSemester = nullptr, *curCourse;
    for (Node<Course>* cur = allData.allCourses; cur; cur = cur->next) {
        Course course = cur->data;

        if (course.schoolYearName == schoolYear &&
            course.semesterNumber == semesterNumber) {
            pushToEndLinkedList(allCourseOfSemester, curCourse, course);
        }
    }

    return allCourseOfSemester;
}
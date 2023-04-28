#include "GetAllCoursesOfStudentsInClass.h"

#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../Check/CheckStudentID/CheckStudentID.h"

bool listHasCourse(Node<std::string>* allCourses, std::string fullCourseName) {
    while (allCourses) {
        if (allCourses->data == fullCourseName) {
            return true;
        }
        allCourses = allCourses->next;
    }

    return false;
}

Node<std::string>* getAllCoursesOfStudentsInClass(Node<Score>* allScoresOfClass) {
    Node<std::string>*allCoursesOfStudentsInClass = nullptr, *cur;

    while (allScoresOfClass) {
        std::string fullCourseName = allScoresOfClass->data.studentCourse.courseID + "-" +
                                     allScoresOfClass->data.studentCourse.className;

        if (!listHasCourse(allCoursesOfStudentsInClass, fullCourseName)) {
            pushToEndLinkedList(allCoursesOfStudentsInClass, cur, fullCourseName);
        }

        allScoresOfClass = allScoresOfClass->next;
    }

    return allCoursesOfStudentsInClass;
}

int getCourseCredits(
    Node<Course>* allCourses, const std::string& courseID, const std::string& className
) {
    for (; allCourses; allCourses = allCourses->next) {
        if (allCourses->data.id == courseID && allCourses->data.className == className) {
            return allCourses->data.credits;
        }
    }

    return 0;
}

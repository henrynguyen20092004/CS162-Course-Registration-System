#include "CheckCourse.h"

bool checkCourseExists(
    Node<Course> *allCourses, const std::string &courseID, const std::string &className
) {
    for (; allCourses; allCourses = allCourses->next) {
        Course course = allCourses->data;

        if (course.className == className && course.id == courseID) {
            return true;
        }
    }

    return false;
}

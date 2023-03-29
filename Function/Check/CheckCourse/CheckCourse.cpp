#include "CheckCourse.h"

bool checkCourseExists(
    Node<Course> *allCourse, const std::string &courseID, const std::string &className
) {
    for (; allCourse; allCourse = allCourse->next) {
        Course course = allCourse->data;

        if (course.className == className && course.id == courseID) {
            return true;
        }
    }

    return false;
}

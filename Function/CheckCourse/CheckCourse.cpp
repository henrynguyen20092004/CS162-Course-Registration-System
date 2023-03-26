#include "CheckCourse.h"

bool checkCourseExist(
    Node<Course> *allCourse, const std::string &courseID, const std::string &className
) {
    while (allCourse) {
        if (allCourse->data.className == className && allCourse->data.id == courseID) {
            return true;
        }

        allCourse = allCourse->next;
    }

    return false;
}

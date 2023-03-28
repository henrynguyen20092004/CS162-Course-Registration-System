#include "ValidateCourse.h"

#include "../DateFunction/DateFunction.h"

void validateCourseAndClass(
    Node<Course> *allCourses, Node<std::string> *allClasses, const Course &course
) {
    if (!checkClassExists(allClasses, course.className)) {
        throw std::invalid_argument("This class does not exist. Please try again!\n");
    }

    if (checkCourseExists(allCourses, course.id, course.className)) {
        throw std::invalid_argument("This course already exists, please try again!\n");
    }
}

void validateOtherInformation(const Course &course) {
    if (course.credits < 1) {
        throw std::invalid_argument("Invalid credits number, please try again!\n");
    }

    if (course.maxStudent < 1) {
        throw std::invalid_argument(
            "Invalid maximum number of students, please try again!\n"
        );
    }

    if (!checkDayOfWeek(course.dayOfWeek)) {
        throw std::invalid_argument("Invalid day of week, please try again!\n");
    }

    if (course.sessionNumber < 1 || course.sessionNumber > 4) {
        throw std::invalid_argument("Invalid session number, please try again!\n");
    }
}

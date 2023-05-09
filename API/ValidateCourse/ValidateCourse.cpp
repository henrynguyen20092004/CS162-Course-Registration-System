#include "ValidateCourse.h"

#include <stdexcept>

void validateCourse(const Course &course) {
    if (course.credits < 1) {
        throw std::invalid_argument("Invalid credits number, please try again!");
    }

    if (course.maxStudent < 1) {
        throw std::invalid_argument(
            "Invalid maximum number of students, please try again!"
        );
    }
}

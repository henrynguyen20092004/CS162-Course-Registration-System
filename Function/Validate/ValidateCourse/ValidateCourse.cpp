#include "ValidateCourse.h"

#include <stdexcept>

#include "../../DateFunction/DateFunction.h"

void validateCourse(const Course &course) {
    if (course.credits < 1) {
        throw std::invalid_argument("Invalid credits number, please try again!");
    }

    if (course.maxStudent < 1) {
        throw std::invalid_argument(
            "Invalid maximum number of students, please try again!"
        );
    }

    if (!checkDayOfWeek(course.dayOfWeek)) {
        throw std::invalid_argument("Invalid day of week, please try again!");
    }

    if (course.sessionNumber < 1 || course.sessionNumber > 4) {
        throw std::invalid_argument("Invalid session number, please try again!");
    }
}

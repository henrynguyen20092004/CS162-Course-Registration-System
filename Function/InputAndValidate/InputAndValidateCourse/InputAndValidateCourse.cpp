#include "InputAndValidateCourse.h"

#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../DateFunction/DateFunction.h"

void inputCourseIDAndClassName(Course &course) {
    std::cout << "Please enter the course's id: ";
    getline(std::cin, course.id);
    std::cout << "Please the course's class: ";
    getline(std::cin, course.className);
}

void inputOtherCourseInformation(Course &course) {
    std::cout << "Please enter the course name: ";
    getline(std::cin, course.name);
    std::cout << "Please enter the teacher name: ";
    // course.teacherName = nameInput();
    std::cout << "Please enter the number of credits of this course: ";
    // course.credits = intInput();
    std::cout << "Please enter the maximum number of students in the course: ";
    // course.maxStudent = intInput();
    std::cout << "Please choose the day of week that the course will be perfomed "
                 "(MON/TUE/WED/THU/FRI/SAT): ";
    getline(std::cin, course.dayOfWeek);
    std::cout << "Please choose the session number that the course will be perfomed: ";
    // course.sessionNumber = intInput();
}

void validateCourseIDAndClass(
    Node<Course> *allCourses, const Course &course, bool checkCourseAlreadyExists
) {
    if (checkCourseExists(allCourses, course.id, course.className) ==
        checkCourseAlreadyExists) {
        if (checkCourseAlreadyExists) {
            throw std::invalid_argument("This course already exists, please try again!");
        } else {
            throw std::invalid_argument("This course does not exist, please try again!");
        }
    }
}

void validateOtherCourseInformation(const Course &course) {
    if (course.name == "") {
        throw std::invalid_argument("Please enter a course name!");
    }

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

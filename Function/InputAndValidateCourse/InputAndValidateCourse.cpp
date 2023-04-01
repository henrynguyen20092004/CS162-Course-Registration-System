#include "InputAndValidateCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../DateFunction/DateFunction.h"
#include "../Input/Input.h"

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
    course.teacherName = nameInput();
    std::cout << "Please enter the number of credits of this course: ";
    course.credits = intInput();
    std::cout << "Please enter the maximum number of students in the course: ";
    course.maxStudent = intInput();
    std::cout << "Please choose the day of week that the course will be perfomed "
                 "(MON/TUE/WED/THU/FRI/SAT): ";
    getline(std::cin, course.dayOfWeek);
    std::cout << "Please choose the session number that the course will be perfomed: ";
    course.sessionNumber = intInput();
}

void validateCourseIDAndClass(
    Node<Course> *allCourses, Node<std::string> *allClasses, const Course &course
) {
    if (!checkClassExists(allClasses, course.className)) {
        throw std::invalid_argument(
            "This class does not exist, please create it or try again!\n"
        );
    }

    if (checkCourseExists(allCourses, course.id, course.className)) {
        throw std::invalid_argument("This course already exists, please try again!\n");
    }
}

void validateOtherCourseInformation(const Course &course) {
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

#include "InputCourse.h"

#include "../Input/Input.h"

void inputCourseIDAndClassName(Course& course) {
    std::cout << "Please enter the course's id: ";
    getline(std::cin, course.id);
    std::cout << "Please the course's class: ";
    getline(std::cin, course.className);
}

void inputOtherInformation(Course& course) {
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

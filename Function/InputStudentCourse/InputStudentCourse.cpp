#include "InputStudentCourse.h"

void inputStudent_Course(Student_Course &studentCourse) {
    std::cout << "Please enter the student's id: ";
    getline(std::cin, studentCourse.studentID);
    std::cout << "Please enter the id of the student's course: ";
    getline(std::cin, studentCourse.courseID);
    std::cout << "Please enter the class name of this course: ";
    getline(std::cin, studentCourse.className);
}

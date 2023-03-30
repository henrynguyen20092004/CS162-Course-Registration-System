#include "InputStudentCourse.h"

void inputStudent_Course(Student_Course &student_course) {
    std::cout << "Please enter the student's id: ";
    getline(std::cin, student_course.studentID);
    std::cout << "Please enter the id of the student's course: ";
    getline(std::cin, student_course.courseID);
    std::cout << "Please enter the class name of this course: ";
    getline(std::cin, student_course.className);
}

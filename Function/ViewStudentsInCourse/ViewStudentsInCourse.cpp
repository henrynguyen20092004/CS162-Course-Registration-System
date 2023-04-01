#include "ViewStudentsInCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../DisplayStudentInfo/DisplayStudentInfo.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../InputAndValidateCourse/InputAndValidateCourse.h"
#include "../SortAndOutputStudents/SortAndOutputStudents.h"

void displayStudentsInCourse(
    std::ostream& out, Student* allStudentsArray, int arraySize
) {
    for (int i = 0; i < arraySize; ++i) {
        out << "\nThis is the student number " << i + 1 << ":\n";
        displayStudentInfo(allStudentsArray[i]);
    }
}

void viewStudentsInCourse() {
    Node<Course>* allCourses = getAllCourses();
    Course course;
    bool validCourse = false;

    do {
        try {
            inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allCourses, course, false);
            validCourse = true;
        } catch (std::exception& error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    Node<Student>* allStudentsInCourse = getAllStudentsInCourse(course);

    if (!allStudentsInCourse) {
        std::cout << "There's no student in this course, please add some!\n";
    }

    sortAndOutputStudents(std::cout, allStudentsInCourse, &displayStudentsInCourse);
    deleteLinkedList(allCourses);
}

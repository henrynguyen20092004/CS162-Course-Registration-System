#include "ViewStudentsInCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../InputCourse/InputCourse.h"
#include "../SortAndDisplayStudent/SortAndDisplayStudent.h"

void viewStudentsInCourse() {
    Node<std::string>* allClasses = getAllClasses();
    Node<Course>* allCourses = getAllCourses();
    Course course;
    bool courseExists;

    do {
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!courseExists);

    Node<Student>* allStudentsInCourse = getAllStudentsInCourse(course);

    if (!allStudentsInCourse) {
        std::cout << "There's no student in this course!\n";
    }

    sortAndDisplayStudent(allStudentsInCourse);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
}

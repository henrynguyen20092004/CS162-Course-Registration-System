#include "ViewStudentInCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../DisplayStudentInfo/DisplayStudentInfo.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../InputCourse/InputCourse.h"
#include "../ValidateCourse/ValidateCourse.h"

void viewStudent(const Course& course) {
    Node<Student_Course>*allStudentsInCourse = getAllStudentsInCourse(course),
    *cur = allStudentsInCourse;
    Node<Student>* allStudents = getAllStudents();
    int counter = 1;

    for (; cur; cur = cur->next) {
        for (Node<Student>* cur2 = allStudents; cur2; cur2 = cur2->next) {
            if (cur->data.studentID == cur2->data.id) {
                std::cout << "\nThis is student number " << counter++ << ":\n";
                displayStudentInfo(cur2->data);
                break;
            }
        }
    }

    deleteLinkedList(allStudentsInCourse);
    deleteLinkedList(allStudents);
}

void viewStudentInCourse() {
    Node<std::string>* allClasses = getAllClasses();
    Node<Course>* allCourses = getAllCourses();
    Course course;
    bool validCourse = false;

    do {
        try {
            inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allCourses, allClasses, course);
            validCourse = true;
        } catch (std::exception& error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    viewStudent(course);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
}

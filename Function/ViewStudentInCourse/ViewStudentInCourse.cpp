#include "ViewStudentInCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../DisplayStudentInfo/DisplayStudentInfo.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"

void validateCourseIDAndClass(
    Node<std::string>* allClasses, Node<Course>* allCourses, const Course& course
) {
    if (!checkClassExists(allClasses, course.className)) {
        throw std::invalid_argument("This class does not exist, please try again!\n");
    }

    if (!checkCourseExists(allCourses, course.id, course.className)) {
        throw std::invalid_argument("This course does not exist, please try again!\n");
    }
}

void inputCourseIDAndClass(Course& course) {
    std::cout << "Please enter the id of course: ";
    getline(std::cin, course.id);
    std::cout << "Please enter the class name of course: ";
    getline(std::cin, course.className);
}

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
            inputCourseIDAndClass(course);
            validateCourseIDAndClass(allClasses, allCourses, course);
            validCourse = true;
        } catch (std::exception& error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    viewStudent(course);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
}

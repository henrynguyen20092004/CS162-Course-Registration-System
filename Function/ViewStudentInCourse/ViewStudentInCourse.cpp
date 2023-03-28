#include "ViewStudentInCourse.h"

#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"

void viewStudent(const Course& course) {
    Node<Student_Course>* allStudentInCourse = getAllStudentsInCourse(course);
    Node<Student>* allStudent = getAllStudents();

    for (Node<Student_Course>* cur = allStudentInCourse; cur; cur = cur->next) {
        for (Node<Student>* tmpAllStudent = allStudent; tmpAllStudent;
             tmpAllStudent = tmpAllStudent->next) {
            if (cur->data.studentID == tmpAllStudent->data.id) {
                std::cout << "This is the student id: " << tmpAllStudent->data.id << '\n';
                std::cout << "First name: " << tmpAllStudent->data.firstName << '\n';
                std::cout << "Last name: " << tmpAllStudent->data.lastName << '\n';
                std::cout << "Gender: " << tmpAllStudent->data.gender << '\n';
                std::cout << "Date of birth: " << tmpAllStudent->data.dateOfBirth << '\n';
                std::cout << "Social ID: " << tmpAllStudent->data.socialID << '\n';
                std::cout << "Class name: " << tmpAllStudent->data.className << "\n\n";
                break;
            }
        }
    }

    deleteLinkedList(allStudentInCourse);
    deleteLinkedList(allStudent);
}

void inputViewCourse(Course& course) {
    std::cout << "Please enter the id of course: ";
    getline(std::cin, course.id);
    std::cout << "Please enter the class name of course: ";
    getline(std::cin, course.className);
}

void viewStudentInCourse() {
    Course course;
    inputViewCourse(course);
    viewStudent(course);
}
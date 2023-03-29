#include "UpdateStudentResult.h"

#include "../../Struct/Score.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../ValidateStudentCourse/ValidateStudentCourse.h"

void inputStudentUpdate(Score &score) {
    std::cout << "Please enter the course id: ";
    getline(std::cin, score.student_course.courseID);
    std::cout << "Please enter the class name: ";
    getline(std::cin, score.student_course.className);
    std::cout << "Please enter the student's id: ";
    getline(std::cin, score.student_course.studentID);
    std::cout << "Please enter the student's fullname: ";
    score.studentFullName = nameInput();
}

void optionUpdate(Score &score) {
    char option;
    std::cout << "Please enter the result of student you want to update: ";
    std::cout << "1.The midterm mark: ";
    std::cout << "2.The final mark: ";
    std::cout << "3.The total mark: ";
    std::cout << "4.The other mark: ";
    double midterMark = 0, finalMark = 0, totalMark = 0, otherMark = 0;
    bool validOption = true;
    do {
        switch (option) {
            case '1': {
                std::cout << "Enter new the midterm mark: ";
                midterMark = doubleInput();
                score.midterMark = midterMark;
                break;
            }
            case '2': {
                std::cout << "Enter new the finalterm mark: ";
                finalMark = doubleInput();
                score.finalMark = finalMark;
                break;
            }
            case '3': {
                std::cout << "Enter new the total mark: ";
                totalMark = doubleInput();
                score.totalMark = totalMark;
                break;
            }
            case '4': {
                std::cout << "Enter new the other mark: ";
                otherMark = doubleInput();
                score.otherMark = otherMark;
                break;
            }
            default: {
                std::cout << "Invalid option, please try again!\n";
                validOption = false;
                break;
            }
        }
    } while (!validOption);
}

void inputUpdate(Score &score) {
    Node<Student> *allStudents = getAllStudents();
    Node<Course> *allCourses = getAllCourses();
    Node<std::string> *allClasses = getAllClasses();
    bool validInput = true;
    do {
        try {
            inputStudentUpdate(score);
            validateStudent_Course(
                allStudents, allClasses, allCourses, score.student_course
            );
            optionUpdate(score);
        } catch (std::exception &error) {
            validInput = false;
            std::cout << error.what();
        }
    } while (!validInput);

    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
}

void updateStudentResult() {
    Node<Course> *allCourses = getAllCourses();

    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }

    Score score;
    inputUpdate(score);
    deleteLinkedList(allCourses);
}

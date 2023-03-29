#include "UpdateStudentResult.h"

#include "../../Struct/Score.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../Input/Input.h"

void inputStudentUpdate() {
    Score score;
    std::cout << "Please enter the student's id: ";
    getline(std::cin, score.studentID);
    std::cout << "Please enter the student's fullname: ";
    score.studentFullName = nameInput();
    std::cout << "Please enter the course id: ";
    getline(std::cin, score.courseID);
}

void inputUpdate(Score &score) {
    std::cout << "Please enter the result of student you want to update: ";
    std::cout << "1.The midterm mark: ";
    std::cout << ""
}

void updateStudentResult() {
    Node<Course> *allCourses = getAllCourses();

    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }
}
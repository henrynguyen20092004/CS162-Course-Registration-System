#include "InputAndValidateStudentCourse.h"

#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../Check/CheckStudent/CheckStudent.h"

void inputStudentCourse(StudentCourse &studentCourse) {
    std::cout << "Please enter the student's id: ";
    getline(std::cin, studentCourse.studentID);
    std::cout << "Please enter the id of the student's course: ";
    getline(std::cin, studentCourse.courseID);
    std::cout << "Please enter the class name of this course: ";
    getline(std::cin, studentCourse.className);
}

void validateStudentCourse(
    Node<Student> *allStudents, Node<std::string> *allClasses, Node<Course> *allCourses,
    const StudentCourse &studentCourse
) {
    if (!checkStudentIDExists(allStudents, studentCourse.studentID)) {
        throw std::invalid_argument(
            "This student does not exist, please create one or try again!"
        );
    }

    if (!checkClassExists(allClasses, studentCourse.className)) {
        throw std::invalid_argument("This class does not exist, please try again!");
    }

    if (!checkCourseExists(allCourses, studentCourse.courseID, studentCourse.className)) {
        throw std::invalid_argument("This course does not exist, please try again!");
    }
}

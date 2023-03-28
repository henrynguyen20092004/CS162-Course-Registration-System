#include "AddStudentToCourse.h"

#include "../../Struct/Student_Course.h"
#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"

void validateStudent_Course(
    Node<Student> *allStudent, Node<std::string> *allClass, Node<Course> *allCourse,
    const Student_Course &studentCourse
) {
    if (!checkStudentIDExists(allStudent, studentCourse.studentID)) {
        throw std::invalid_argument("This student does not exist, please try again!\n");
    }

    if (!checkClassExists(allClass, studentCourse.className)) {
        throw std::invalid_argument("This class does not exist, please try again!\n");
    }

    if (!checkCourseExists(allCourse, studentCourse.courseID, studentCourse.className)) {
        throw std::invalid_argument("This course does not exist, please try again!\n");
    }
}

void inputStudent_Course(Student_Course &studentCourse) {
    std::cout << "Please enter the student's id: ";
    getline(std::cin, studentCourse.studentID);
    std::cout << "Please enter the id of the student's course: ";
    getline(std::cin, studentCourse.courseID);
    std::cout << "Please enter the class name of this course: ";
    getline(std::cin, studentCourse.className);
}

void saveStudentToCourse(const Student_Course &studentCourse) {
    std::ofstream fout;
    writeFile(fout, "Data/Student_Course.txt", std::ios::app);
    fout << studentCourse.studentID << '\n';
    fout << studentCourse.courseID << '-' << studentCourse.className << '\n';
    fout.close();
}

void addStudentToCourse() {
    Student_Course studentCourse;
    Node<Student> *allStudent = getAllStudents();
    Node<std::string> *allClass = getAllClasses();
    Node<Course> *allCourse = getAllCourses();
    bool validStudent_Course = false;

    do {
        try {
            inputStudent_Course(studentCourse);
            validateStudent_Course(allStudent, allClass, allCourse, studentCourse);
            validStudent_Course = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudent_Course);

    saveStudentToCourse(studentCourse);
    deleteLinkedList(allStudent);
    deleteLinkedList(allClass);
    deleteLinkedList(allCourse);
}

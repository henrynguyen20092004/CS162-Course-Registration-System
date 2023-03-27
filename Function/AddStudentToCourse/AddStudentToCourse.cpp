#include "AddStudentToCourse.h"

#include "../../Struct/Student_Course.h"
#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../GetAlL/GetAllStudents/GetAllStudents.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"

bool checkCourseIDExist(Node<Course> *course, const std::string &courseID) {
    while (course) {
        if (course->data.id == courseID) {
            return true;
        }
        course = course->next;
    }
    return false;
}

void inputStudent(Student_Course &studentCourse) {
    Node<Student> *allStudent = getAllStudents();
    bool checkStudentExist = false, checkClassNameExist = false, checkCourseExist = false;

    do {
        std::cout << "Please enter student id: ";
        getline(std::cin, studentCourse.studentID);
        checkStudentExist = checkStudentIDExists(allStudent, studentCourse.studentID);
        if (!checkStudentExist) {
            std::cout << "This student does not exist. Please try again!\n";
        }
    } while (!checkStudentExist);
    deleteLinkedList(allStudent);

    Node<std::string> *allClassName = getAllClasses();
    do {
        std::cout << "Please enter class name that he/she are learning: ";
        getline(std::cin, studentCourse.className);
        checkClassNameExist = checkClassExists(allClassName, studentCourse.className);
        if (!checkClassNameExist) {
            std::cout << "This class does not exist. Please try again!\n";
        }
    } while (!checkClassNameExist);
    deleteLinkedList(allClassName);

    Node<Course> *allCourses = getAllCourses();
    do {
        std::cout << "Please enter course id to add he/she into: ";
        getline(std::cin, studentCourse.courseID);
        checkCourseExist = checkCourseIDExist(allCourses, studentCourse.courseID);
        if (!checkCourseExist) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!checkCourseExist);
    deleteLinkedList(allCourses);
}

void saveStudentToCourse(Student_Course studentCourse) {
    std::ofstream fout;
    writeFile(fout, "Data/Student_Course.txt", std::ios::app);
    fout << studentCourse.studentID << "-" << studentCourse.courseID << '\n';
    fout << studentCourse.className << '\n';
    fout.close();
}

void addStudentToCourse() {
    Student_Course studentCourse;
    inputStudent(studentCourse);
    saveStudentToCourse(studentCourse);
}

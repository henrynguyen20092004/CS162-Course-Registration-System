#include "AddStudentToCourse.h"

#include "../../Struct/Student_Course.h"
#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"

void inputStudent_Course(Student_Course &studentCourse) {
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClass = getAllClasses();
    bool checkStudentExist = false, checkClassExist = false, checkCourseExist = false;

    do {
        std::cout << "Please enter student id: ";
        getline(std::cin, studentCourse.studentID);
        checkStudentExist = checkStudentIDExists(allStudents, studentCourse.studentID);
        if (!checkStudentExist) {
            std::cout << "This student does not exist, please try again!\n";
        }
    } while (!checkStudentExist);
    deleteLinkedList(allStudents);

    do {
        std::cout << "Please enter class name that he/she are learning: ";
        getline(std::cin, studentCourse.className);

        checkClassExist = checkClassExists(allClass, studentCourse.className);
        if (!checkClassExist) {
            std::cout << "This class does not exist, please try again!\n";
        }
    } while (!checkClassExists);
    deleteLinkedList(allClass);

    Node<Course> *allCourses = getAllCourses();
    do {
        std::cout << "Please enter course id to add he/she into: ";
        getline(std::cin, studentCourse.courseID);
        checkCourseExist = checkCourseExists(
            allCourses, studentCourse.courseID, studentCourse.className
        );
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
    inputStudent_Course(studentCourse);
    saveStudentToCourse(studentCourse);
}

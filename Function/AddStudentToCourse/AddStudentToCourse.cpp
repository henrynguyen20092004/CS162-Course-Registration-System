#include "AddStudentToCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputAndValidate/InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"

void saveStudentToCourse(const StudentCourse &studentCourse) {
    std::ofstream fout;
    writeFile(fout, "Data/StudentCourse.txt", std::ios::app);
    fout << studentCourse.studentID << '\n';
    fout << studentCourse.courseID << '\n';
    fout << studentCourse.className << '\n';
    fout.close();
}

void addStudentToCourse() {
    StudentCourse studentCourse;
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    bool validStudentCourse = false;

    do {
        try {
            inputStudentCourse(studentCourse);
            validateStudentCourse(allStudents, allClasses, allCourses, studentCourse);
            validStudentCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudentCourse);

    saveStudentToCourse(studentCourse);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
    std::cout << "Student successfully added!\n";
}

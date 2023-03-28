#include "AddStudentToCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputStudentCourse/InputStudentCourse.h"
#include "../ValidateStudentCourse/ValidateStudentCourse.h"

void saveStudentToCourse(const Student_Course &studentCourse) {
    std::ofstream fout;
    writeFile(fout, "Data/Student_Course.txt", std::ios::app);
    fout << studentCourse.studentID << '\n';
    fout << studentCourse.courseID << '-' << studentCourse.className << '\n';
    fout.close();
}

void addStudentToCourse() {
    Student_Course studentCourse;
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    bool validStudent_Course = false;

    do {
        try {
            inputStudent_Course(studentCourse);
            validateStudent_Course(allStudents, allClasses, allCourses, studentCourse);
            validStudent_Course = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudent_Course);

    std::cout << "Student added successfully!\n";

    saveStudentToCourse(studentCourse);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
}

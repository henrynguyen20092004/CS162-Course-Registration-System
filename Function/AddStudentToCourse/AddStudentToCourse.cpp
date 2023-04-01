#include "AddStudentToCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"

void saveStudentToCourse(const Student_Course &student_course) {
    std::ofstream fout;
    writeFile(fout, "Data/Student_Course.txt", std::ios::app);
    fout << student_course.studentID << '\n';
    fout << student_course.courseID << '\n';
    fout << student_course.className << '\n';
    fout.close();
}

void addStudentToCourse() {
    Student_Course student_course;
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    bool validStudent_Course = false;

    do {
        try {
            inputStudentCourse(student_course);
            validateStudent_Course(allStudents, allClasses, allCourses, student_course);
            validStudent_Course = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudent_Course);

    saveStudentToCourse(student_course);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
    std::cout << "Student successfully added!\n";
}

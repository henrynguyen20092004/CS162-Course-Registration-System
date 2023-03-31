#include "ExportStudentInCourse.h"

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../OpenFile/OpenFile.h"

void exportStudentsInCourse() {
    Course course;
    Node<Course> *allCourse = getAllCourses();
    bool existCourse;
    do {
        std::cout << "Please enter the course you want to export its students: ";
        getline(std::cin, course.id);
        std::cout << "Please enter the class of this course: ";
        getline(std::cin, course.className);
        existCourse = checkCourseExists(allCourse, course.id, course.className);
        if (!existCourse) {
            std::cout << "This course doesn't exist, please try again\n";
        }
    } while (!existCourse);

    std::ofstream fout;
    Node<Student> *studentInCourse = getAllStudentsInCourse(course);
    if (!studentInCourse) {
        std::cout << "This course is blank";
    }
    writeFile(fout, "ExportCSV/StudentInCourse.csv");
    while (studentInCourse) {
        fout << studentInCourse->data.id << ",";
        fout << studentInCourse->data.firstName << ",";
        fout << studentInCourse->data.lastName << ",";
        fout << studentInCourse->data.gender << ",";
        fout << studentInCourse->data.dateOfBirth << ",";
        fout << studentInCourse->data.socialID << ",";
        fout << studentInCourse->data.className << '\n';
        studentInCourse = studentInCourse->next;
    }
    fout.close();
    std::cout << "Successfully export!\n";
    deleteLinkedList(studentInCourse);
}
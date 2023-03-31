#include "ImportStudentInCourse.h"

#include <string.h>

#include <sstream>

#include "../../Struct/Student.h"
#include "../../Struct/Student_Course.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../DownloadTemplateCSV/DownloadTemplateCSV.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../InputCourse/InputCourse.h"
#include "../ShowCSVErrorLines/ShowCSVErrorLines.h"
#include "../ValidateStudent/ValidateStudent.h"

void getStudentFromLine(Student &student, const std::string &importLine) {
    std::string _;
    std::istringstream importStream(importLine);
    getline(importStream, _, ',');
    getline(importStream, student.id, ',');
    getline(importStream, student.firstName, ',');
    getline(importStream, student.lastName, ',');
    getline(importStream, student.gender, ',');
    getline(importStream, student.dateOfBirth, ',');
    getline(importStream, student.socialID, ',');
    getline(importStream, student.className, ',');
}

void importStudentsInCourse() {
    std::ifstream fin;
    std::ofstream fout;
    std::string importPath, importLine, _;
    bool courseExists, validPath, studentIDExists, studentExistedInCourse = false;
    int curLine = 1;
    Course course;
    Student student;
    Student_Course student_course;
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    Node<Student> *allStudents = getAllStudents();
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;

    do {
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!courseExists);

    student_course.courseID = course.id;
    student_course.className = course.className;

    Node<Student_Course> *allStudents_Courses = getAllStudent_Courses();

    do {
        try {
            std::cout << "Please enter the path to the CSV: ";
            getline(std::cin, importPath);

            if (importPath == "") {
                std::cout << "Please enter a path!\n";
                continue;
            }

            readFile(fin, importPath);
            writeFile(fout, "Student_Course.txt", std::ios::app);
            getline(fin, _);

            while (fin.good()) {
                getline(fin, importLine);

                if (!fin.good()) {
                    break;
                }

                ++curLine;

                try {
                    getStudentFromLine(student, importLine);
                    validateStudent(allStudents, allClasses, student, false);
                    studentExistedInCourse = checkStudentInCourse(
                        allStudents_Courses, student.id, course.id, course.className
                    );
                    if (studentExistedInCourse) {
                        throw std::invalid_argument("Duplicated record");
                    }
                } catch (std::invalid_argument &error) {
                    if (!strcmp(error.what(), "Duplicated record")) {
                        pushToEndLinkedList(duplicateErrors, curDuplicateErrors, curLine);
                    } else {
                        pushToEndLinkedList(invalidErrors, curInvalidErrors, curLine);
                    }
                    continue;
                } catch (...) {
                    continue;
                }

                fout << student.id << '\n'
                     << course.id << '\n'
                     << course.className << '\n';
            }

            validPath = true;
            fin.close();
            fout.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    showCSVErrorLines(duplicateErrors, "The following line(s) are duplicated:");
    showCSVErrorLines(invalidErrors, "The following line(s) have invalid student ID(s):");
    deleteLinkedList(allStudents_Courses);
    deleteLinkedList(allCourses);
    deleteLinkedList(allClasses);
    deleteLinkedList(allStudents);
}

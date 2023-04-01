#include "ImportStudentInCourse.h"

#include <string.h>

#include <sstream>

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../InputAndValidateCourse/InputAndValidateCourse.h"
#include "../SaveCourse/SaveCourse.h"
#include "../SaveStudent/SaveStudent.h"
#include "../ShowCSVErrorLines/ShowCSVErrorLines.h"

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
    getline(importStream, student.className);
}

void validateStudentRecord(
    Student &student, Node<Student> *allStudents, Node<std::string> *allClasses,
    Node<Student_Course> *allStudentCourse, const Course &course,
    Node<Student> *allStudentsInCourse
) {
    allStudents = new Node(allStudents);

    if (student.gender == "M" || student.gender == "m") {
        student.gender = "M";
    } else if (student.gender == "F" || student.gender == "f") {
        student.gender = "F";
    } else {
        throw std::invalid_argument("Invalid gender, please try again!\n");
    }

    if (!checkDate(student.dateOfBirth)) {
        throw std::invalid_argument("Invalid date of birth, please try again!\n");
    }

    if (!checkClassExists(allClasses, student.className)) {
        throw std::invalid_argument("This class doesn't exists, please try again!\n");
    }

    for (; allStudentsInCourse; allStudentsInCourse = allStudentsInCourse->next) {
        if (allStudentsInCourse->data == student) {
            throw std::invalid_argument("Duplicated record");
        }
    }

    for (; allStudents->next; allStudents = allStudents->next) {
        if (allStudents->next->data.id == student.id) {
            allStudents->next->data = student;
            break;
        }
    }

    if (!allStudents->next) {
        allStudents->next = new Node(student);
    }

    Node<Student> *tmpStudent = allStudents;
    allStudents = allStudents->next;
    delete tmpStudent;

    if (checkStudentInCourse(allStudentCourse, student.id, course.id, course.className)) {
        throw std::runtime_error("Student updated successfully!");
    }
}

void importStudentsInCourse() {
    std::ifstream fin;
    std::string importPath, importLine, _;
    bool courseExists, validPath = false;
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

    Node<Student_Course> *allStudentCourse = getAllStudent_Courses(), *cur;
    Node<Student> *allStudentsInCourse = getAllStudentsInCourse(course);

    do {
        try {
            std::cout << "Please enter the path to the CSV: ";
            getline(std::cin, importPath);

            if (importPath == "") {
                std::cout << "Please enter a path!\n";
                continue;
            }

            readFile(fin, importPath);
            getline(fin, _);

            while (fin.good()) {
                getline(fin, importLine);

                if (importLine == "") {
                    break;
                }

                ++curLine;

                try {
                    getStudentFromLine(student, importLine);
                    validateStudentRecord(
                        student, allStudents, allClasses, allStudentCourse, course,
                        allStudentsInCourse
                    );
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

                student_course.studentID = student.id;
                pushToEndLinkedList(allStudentCourse, cur, student_course);
            }

            validPath = true;
            fin.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    saveAllStudents(allStudents);
    saveAllStudent_Courses(allStudentCourse);
    showCSVErrorLines(duplicateErrors, "The following line(s) are duplicated:");
    showCSVErrorLines(invalidErrors, "The following line(s) have invalid student ID(s):");
    deleteLinkedList(allStudentsInCourse);
    deleteLinkedList(allStudentCourse);
    deleteLinkedList(allCourses);
    deleteLinkedList(allClasses);
    deleteLinkedList(allStudents);
    deleteLinkedList(duplicateErrors);
    deleteLinkedList(invalidErrors);
    std::cout << "Students successfully imported into course!\n";
}

#include "ImportStudentInCourse.h"

#include <cstring>
#include <sstream>

#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../Check/CheckStudentID/CheckStudentID.h"
#include "../../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../../Create/CreateStudentAccount/CreateStudentAccount.h"
#include "../../DateFunction/DateFunction.h"
#include "../../GetAll/GetAllClasses/GetAllClasses.h"
#include "../../GetAll/GetAllCourses/GetAllCourses.h"
#include "../../GetAll/GetAllStudents/GetAllStudents.h"
#include "../../GetAll/GetAllUsers/GetAllUsers.h"
#include "../../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../../InputAndValidate/InputAndValidateStudent/InputAndValidateStudent.h"
#include "../../OperatorOverload/OperatorOverload.h"
#include "../../Save/SaveCourse/SaveCourse.h"
#include "../../Save/SaveStudent/SaveStudent.h"
#include "../../Save/SaveUser/SaveUser.h"
#include "../../ShowCSVErrorLines/ShowCSVErrorLines.h"
#include "../../Update/UpdateDefaultStudentPassword/UpdateDefaultStudentPassword.h"

void getStudentInCourseFromLine(Student &student, const std::string &importLine) {
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

void checkImportedStudentInCourse(
    Student &student, Node<std::string> *allClasses, Node<Student> *allStudents,
    Node<StudentCourse> *allStudentCourses, Node<User> *allUsers,
    const StudentCourse &studentCourse
) {
    validateStudent(allClasses, student);

    for (Node<Student> *curStudent = allStudents; curStudent;
         curStudent = curStudent->next) {
        if (curStudent->data == student) {
            if (checkStudentInCourse(
                    allStudentCourses, student.id, studentCourse.courseID,
                    studentCourse.className
                )) {
                throw std::invalid_argument("Duplicated record");
            } else {
                if (!allStudentCourses) {
                    return;
                }

                for (; allStudentCourses->next;
                     allStudentCourses = allStudentCourses->next);
                allStudentCourses->next = new Node(studentCourse);
                throw std::runtime_error("Record added");
            }
        } else if (curStudent->data.id == student.id) {
            updateDefaultStudentPassword(allStudents, allUsers, student);
            curStudent->data = student;

            if (!checkStudentInCourse(
                    allStudentCourses, student.id, studentCourse.courseID,
                    studentCourse.className
                )) {
                if (!allStudentCourses) {
                    return;
                }

                for (; allStudentCourses->next;
                     allStudentCourses = allStudentCourses->next);
                allStudentCourses->next = new Node(studentCourse);
            }

            throw std::runtime_error("Record added");
        }
    }
}

void importStudentsInCourse() {
    std::string importPath, importLine, _;
    bool courseExists, validPath = false;
    int curLine = 1;
    Course course;
    Student student;
    StudentCourse studentCourse;
    Node<User> *newUsers = nullptr, *curUser, *allUsers = getAllUsers();
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    Node<StudentCourse> *newStudentCourses = nullptr, *curStudentCourse,
                        *allStudentCourses = getAllStudentCourses();
    Node<Student> *newStudents = nullptr, *curStudent, *allStudents = getAllStudents();
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;

    do {
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist, please try again!\n";
        }
    } while (!courseExists);

    studentCourse.courseID = course.id;
    studentCourse.className = course.className;

    do {
        try {
            std::cout << "Please enter the path to the CSV: ";
            getline(std::cin, importPath);

            if (importPath == "") {
                std::cout << "Please enter a path!\n";
                continue;
            }

            std::ifstream fin;
            readFile(fin, importPath);
            getline(fin, _);

            while (fin.good()) {
                getline(fin, importLine);

                if (!fin.good()) {
                    break;
                }

                ++curLine;

                try {
                    getStudentInCourseFromLine(student, importLine);
                    studentCourse.studentID = student.id;
                    checkImportedStudentInCourse(
                        student, allClasses, allStudents, allStudentCourses, allUsers,
                        studentCourse
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

                pushToEndLinkedList(newStudentCourses, curStudentCourse, studentCourse);
                pushToEndLinkedList(newStudents, curStudent, student);
                User newStudentAccount = createAccount(student);
                pushToEndLinkedList(newUsers, curUser, newStudentAccount);
            }

            validPath = true;
            fin.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    showCSVErrorLines(duplicateErrors, invalidErrors);
    addNewListToOldList(allStudents, newStudents);
    addNewListToOldList(allStudentCourses, newStudentCourses);
    addNewListToOldList(allUsers, newUsers);
    saveAllUsers(allUsers);
    saveAllStudents(allStudents);
    saveAllStudentCourses(allStudentCourses);
    deleteLinkedList(allStudentCourses);
    deleteLinkedList(allCourses);
    deleteLinkedList(allClasses);
    deleteLinkedList(allStudents);
    deleteLinkedList(allUsers);
    deleteLinkedList(duplicateErrors);
    deleteLinkedList(invalidErrors);
    std::cout << "Student successfully imported to course!\n";
}

#include "ImportStudentInCourse.h"

#include <cstring>
#include <sstream>

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckStudent/CheckStudent.h"
#include "../../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../../Create/CreateStudentAccount/CreateStudentAccount.h"
#include "../../InputAndValidate/InputAndValidateStudent/InputAndValidateStudent.h"
#include "../../OperatorOverload/OperatorOverload.h"
#include "../../Save/SaveCourse/SaveCourse.h"
#include "../../Save/SaveStudent/SaveStudent.h"
#include "../../Save/SaveUser/SaveUser.h"
#include "../../ShowCSVErrorLines/ShowCSVErrorLines.h"
#include "../../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"
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
    Student &student, Node<Student> *allStudents, Node<StudentCourse> *&allStudentCourses,
    const StudentCourse &studentCourse
) {
    Node<StudentCourse> *newNode = new Node(studentCourse);
    validateStudent(GlobalVar::allData.allClasses, student);

    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data == student) {
            if (checkStudentInCourse(allStudentCourses, studentCourse)) {
                delete newNode;
                throw std::invalid_argument("Duplicated record");
            } else {
                if (!allStudentCourses) {
                    allStudentCourses = newNode;
                    throw std::runtime_error("Record added");
                }

                Node<StudentCourse> *cur = allStudentCourses;
                for (; cur->next; cur = cur->next)
                    ;
                cur->next = newNode;
                throw std::runtime_error("Record added");
            }
        } else if (allStudents->data.id == student.id) {
            updateDefaultStudentPassword(
                allStudents, GlobalVar::allData.allUsers, student
            );
            allStudents->data = student;

            if (!checkStudentInCourse(allStudentCourses, studentCourse)) {
                if (!allStudentCourses) {
                    allStudentCourses = newNode;
                    throw std::runtime_error("Record added");
                }

                Node<StudentCourse> *cur = allStudentCourses;
                for (; cur->next; cur = cur->next)
                    ;
                cur->next = newNode;
            } else {
                delete newNode;
            }

            throw std::runtime_error("Record added");
        }
    }
}

void importStudentsInCourse(
    char **inputs, char **dropDownItems, const std::string &course
) {
    int curLine = 1;
    Student student;
    StudentCourse studentCourse;
    Node<User> *newUsers = nullptr, *curUser;
    Node<StudentCourse> *newStudentCourses = nullptr, *curStudentCourse;
    Node<Student> *newStudents = nullptr, *curStudent;
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;
    std::string *courseIDAndClassName = new std::string[2], importPath = inputs[1],
                importLine, _;

    splitCourseToIDAndClassName(courseIDAndClassName, course);
    studentCourse.courseID = courseIDAndClassName[0];
    studentCourse.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

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
                student, GlobalVar::allData.allStudents,
                GlobalVar::allData.allStudentCourses, studentCourse
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

    fin.close();
    addNewItemsToOldList(GlobalVar::allData.allStudents, newStudents);
    addNewItemsToOldList(GlobalVar::allData.allStudentCourses, newStudentCourses);
    addNewItemsToOldList(GlobalVar::allData.allUsers, newUsers);
    saveAllUsers(GlobalVar::allData.allUsers);
    saveAllStudents(GlobalVar::allData.allStudents);
    saveAllStudentCourses(GlobalVar::allData.allStudentCourses);
    showCSVErrorLines(duplicateErrors, invalidErrors);
}

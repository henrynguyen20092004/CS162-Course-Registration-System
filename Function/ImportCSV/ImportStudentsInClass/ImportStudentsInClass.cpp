#include "ImportStudentsInClass.h"

#include <cstring>
#include <sstream>

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckStudentID/CheckStudentID.h"
#include "../../Create/CreateStudentAccount/CreateStudentAccount.h"
#include "../../DateFunction/DateFunction.h"
#include "../../InputAndValidate/InputAndValidateStudent/InputAndValidateStudent.h"
#include "../../OpenFile/OpenFile.h"
#include "../../OperatorOverload/OperatorOverload.h"
#include "../../Save/SaveStudent/SaveStudent.h"
#include "../../Save/SaveUser/SaveUser.h"
#include "../../ShowCSVErrorLines/ShowCSVErrorLines.h"
#include "../../Update/UpdateDefaultStudentPassword/UpdateDefaultStudentPassword.h"

void getStudentInClassFromLine(Student &student, std::string importLine) {
    std::string _;
    std::istringstream importStream(importLine);
    getline(importStream, _, ',');
    getline(importStream, student.id, ',');
    getline(importStream, student.firstName, ',');
    getline(importStream, student.lastName, ',');
    getline(importStream, student.gender, ',');
    getline(importStream, student.dateOfBirth, ',');
    getline(importStream, student.socialID);
}

void checkImportedStudentInClass(Node<Student> *allStudents, Student &student) {
    validateStudent(allData.allClasses, student);

    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data == student) {
            throw std::invalid_argument("Duplicated record");
        } else if (allStudents->data.id == student.id) {
            updateDefaultStudentPassword(allStudents, allData.allUsers, student);
            allStudents->data = student;
            throw std::runtime_error("Record updated");
        }
    }
}

void importStudentsInClass() {
    std::string className, importPath, importLine, _;
    bool classExists = false, validPath = false;
    int curLine = 1;
    Student student;
    Node<User> *newUsers = nullptr, *curUser;
    Node<Student> *newStudents = nullptr, *curStudent;
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;

    do {
        std::cout << "Please enter the class' name: ";
        getline(std::cin, className);
        classExists = checkClassExists(allData.allClasses, className);

        if (!classExists) {
            std::cout << "This class doesn't exists, please create it or try again!\n";
        }
    } while (!classExists);

    student.className = className;

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
                    getStudentInClassFromLine(student, importLine);
                    checkImportedStudentInClass(allData.allStudents, student);
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
    addNewItemsToOldList(allData.allStudents, newStudents);
    addNewItemsToOldList(allData.allUsers, newUsers);
    saveAllUsers(allData.allUsers);
    saveAllStudents(allData.allStudents);
    deleteLinkedList(duplicateErrors);
    deleteLinkedList(invalidErrors);
    std::cout << "Student successfully imported to class!\n";
}

#include "ImportStudentsInClass.h"

#include <cstring>
#include <sstream>

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../Create/CreateStudentAccount/CreateStudentAccount.h"
#include "../../DateFunction/DateFunction.h"
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

void validateStudent(Node<std::string> *allClasses, Student &student) {
    if (student.gender == "M" || student.gender == "m") {
        student.gender = "M";
    } else if (student.gender == "F" || student.gender == "f") {
        student.gender = "F";
    } else {
        throw std::invalid_argument("Invalid gender, please try again!");
    }

    if (!checkDate(student.dateOfBirth) ||
        !compareDate(student.dateOfBirth, getToday())) {
        throw std::invalid_argument("Invalid date of birth, please try again!");
    }

    if (!checkClassExists(allClasses, student.className)) {
        throw std::invalid_argument("This class doesn't exists, please try again!");
    }
}

void checkImportedStudentInClass(Node<Student> *allStudents, Student &student) {
    validateStudent(GlobalVar::allData.allClasses, student);

    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data == student) {
            throw std::invalid_argument("Duplicated record");
        } else if (allStudents->data.id == student.id) {
            updateDefaultStudentPassword(
                allStudents, GlobalVar::allData.allUsers, student
            );
            allStudents->data = student;
            throw std::runtime_error("Record updated");
        }
    }
}

void importStudentsInClass(
    char **inputs, char **dropDownItems, const std::string &className
) {
    int curLine = 1;
    Student student;
    Node<User> *newUsers = nullptr, *curUser;
    Node<Student> *newStudents = nullptr, *curStudent;
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;
    std::string importLine;
    student.className = className;

    std::ifstream fin;
    readFile(fin, inputs[1]);
    getline(fin, importLine);

    while (fin.good()) {
        getline(fin, importLine);

        if (!fin.good()) {
            break;
        }

        ++curLine;

        try {
            getStudentInClassFromLine(student, importLine);
            checkImportedStudentInClass(GlobalVar::allData.allStudents, student);
        } catch (std::invalid_argument &error) {
            if (!strcmp(error.what(), "Duplicated record")) {
                pushToEndOfLinkedList(duplicateErrors, curDuplicateErrors, curLine);
            } else {
                pushToEndOfLinkedList(invalidErrors, curInvalidErrors, curLine);
            }

            continue;
        } catch (...) {
            continue;
        }

        pushToEndOfLinkedList(newStudents, curStudent, student);
        User newStudentAccount = createAccount(student);
        pushToEndOfLinkedList(newUsers, curUser, newStudentAccount);
    }

    fin.close();
    addNewItemsToOldList(GlobalVar::allData.allStudents, newStudents);
    addNewItemsToOldList(GlobalVar::allData.allUsers, newUsers);
    saveAllUsers(GlobalVar::allData.allUsers);
    saveAllStudents(GlobalVar::allData.allStudents);
    showCSVErrorLines(duplicateErrors, invalidErrors, curLine);
}

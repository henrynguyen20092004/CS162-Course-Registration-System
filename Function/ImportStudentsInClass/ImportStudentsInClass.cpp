#include "ImportStudentsInClass.h"

#include <cstring>
#include <sstream>

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputAndValidateStudent/InputAndValidateStudent.h"
#include "../OpenFile/OpenFile.h"
#include "../SaveStudent/SaveStudent.h"
#include "../ShowCSVErrorLines/ShowCSVErrorLines.h"

void checkImportedStudent(
    Node<Student> *allStudents, Node<std::string> *allClasses, Student &student
) {
    validateStudent(allClasses, student);

    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data == student) {
            throw std::invalid_argument("Duplicated record");
        } else if (allStudents->data.id == student.id) {
            allStudents->data = student;
            throw std::runtime_error("Record updated");
        }
    }
}

void addNewStudentInClassToOldList(
    Node<Student> *&allStudents, Node<Student> *newStudents
) {
    if (!allStudents) {
        allStudents = newStudents;
        return;
    }

    Node<Student> *cur = allStudents;
    for (; cur->next; cur = cur->next);
    cur->next = newStudents;
}

void getStudentFromLine(Student &student, std::string importLine) {
    std::string _;
    std::istringstream importStream(importLine);
    getline(importStream, _, ',');
    getline(importStream, student.id, ',');
    getline(importStream, student.firstName, ',');
    getline(importStream, student.lastName, ',');
    getline(importStream, student.gender, ',');
    getline(importStream, student.dateOfBirth, ',');
    getline(importStream, student.socialID, '\n');
}

void importStudentsInClass() {
    std::string className, importPath, importLine, _;
    bool classExists = false, validPath = false;
    int curLine = 1;
    Student student;
    Node<Student> *newStudent = nullptr, *cur, *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;

    do {
        std::cout << "Please enter the class' name: ";
        getline(std::cin, className);
        classExists = checkClassExists(allClasses, className);

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
                    getStudentFromLine(student, importLine);
                    checkImportedStudent(allStudents, allClasses, student);
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

                pushToEndLinkedList(newStudent, cur, student);
            }

            validPath = true;
            fin.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    showCSVErrorLines(duplicateErrors, "The following line(s) are duplicated:");
    showCSVErrorLines(invalidErrors, "The following line(s) have invalid record(s):");
    addNewStudentInClassToOldList(allStudents, newStudent);
    saveAllStudents(allStudents);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(duplicateErrors);
    deleteLinkedList(invalidErrors);
    std::cout << "Student successfully imported to class!\n";
}

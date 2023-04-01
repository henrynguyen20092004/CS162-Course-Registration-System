#include "ImportStudentInfo.h"

#include <cstring>
#include <sstream>

#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"
#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../OpenFile/OpenFile.h"
#include "../ShowCSVErrorLines/ShowCSVErrorLines.h"

bool checkFormatOfStudentInfo(
    Node<Student> *allStudents, Node<std::string> *allClasses, Student &student
) {
    if (student.gender != "M" && student.gender != "m" && student.gender != "F" &&
        student.gender != "f")
        return 0;

    if (!checkDate(student.dateOfBirth)) {
        return 0;
    }

    if (!checkClassExists(allClasses, student.className)) {
        return 0;
    }
    return 1;
}

bool compare2Students(Student firstStudent, Student secondStudent) {
    if (firstStudent.id == secondStudent.id &&
        firstStudent.firstName == secondStudent.firstName &&
        firstStudent.lastName == secondStudent.lastName &&
        firstStudent.gender == secondStudent.gender &&
        firstStudent.dateOfBirth == secondStudent.dateOfBirth &&
        firstStudent.socialID == secondStudent.socialID &&
        firstStudent.className == secondStudent.className) {
        return true;
    }
}

void detectDuplicate(
    Node<Student> *allStudents, Node<std::string> *allClasses, Student &student
) {
    for (; allStudents; allStudents = allStudents->next) {
        if (compare2Students(allStudents->data, student)) {
            throw std::invalid_argument("Duplicated record");
        } else if (allStudents->data.id == student.id) {
            allStudents->data.firstName = student.firstName;
            allStudents->data.lastName = student.lastName;
            allStudents->data.gender = student.gender;
            allStudents->data.dateOfBirth = student.dateOfBirth;
            allStudents->data.socialID = student.socialID;
            allStudents->data.className = student.className;
            throw std::runtime_error("Record updated");
        }
    }
}

void saveStudent(Node<Student> *newStudents) {
    std::ofstream fout;
    writeFile(fout, "Data/Student.txt");
    for (; newStudents; newStudents = newStudents->next) {
        Student student = newStudents->data;
        fout << student.id << '\n';
        fout << student.firstName << '\n';
        fout << student.lastName << '\n';
        fout << student.gender << '\n';
        fout << student.dateOfBirth << '\n';
        fout << student.socialID << '\n';
        fout << student.className << '\n';
    }
    fout.close();
    std::cout << "Students successfully added!\n";
}

void addNewStudentToOldList(Node<Student> *&allStudents, Node<Student> *newStudents) {
    if (!allStudents) {
        allStudents = newStudents;
        return;
    }

    Node<Student> *cur = allStudents;
    for (; cur->next; cur = cur->next)
        ;
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
    getline(importStream, student.socialID, ',');
    getline(importStream, student.className, '\n');
}

void importStudents() {
    std::ifstream fin;
    int curLine = 1;
    Node<Student> *newStudent, *cur, *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;
    bool validPath = false;
    std::string importLine, importPath;
    std::string _;

    Student student;

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

                curLine++;

                try {
                    getStudentFromLine(student, importLine);
                    if (!checkFormatOfStudentInfo(allStudents, allClasses, student)) {
                        pushToEndLinkedList(invalidErrors, curInvalidErrors, curLine);
                        continue;
                    }
                    detectDuplicate(allStudents, allClasses, student);
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
    addNewStudentToOldList(allStudents, newStudent);
    saveStudent(allStudents);

    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(duplicateErrors);
    deleteLinkedList(invalidErrors);
    fin.close();
}

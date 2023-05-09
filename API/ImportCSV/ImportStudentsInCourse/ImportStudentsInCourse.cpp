#include "ImportStudentsInCourse.h"

#include <cstring>
#include <sstream>

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../Save/SaveCourse/SaveCourse.h"
#include "../../ShowCSVErrorLines/ShowCSVErrorLines.h"
#include "../../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void getStudentInCourseFromLine(Student &student, const std::string &importLine) {
    std::string part;
    std::istringstream importStream(importLine);
    getline(importStream, part, ',');
    getline(importStream, student.id, ',');
    getline(importStream, part, ',');
    student.firstName = checkAndConvertToName(part, "first name");
    getline(importStream, part, ',');
    student.lastName = checkAndConvertToName(part, "last name");
}

void checkImportedStudentInCourse(
    Student &student, Node<Student> *allStudents, Node<StudentCourse> *&allStudentCourses,
    const StudentCourse &studentCourse
) {
    Node<StudentCourse> *newNode = new Node(studentCourse);

    for (; allStudents; allStudents = allStudents->next) {
        if (allStudents->data.id == student.id) {
            if (allStudents->data.firstName != student.firstName ||
                allStudents->data.lastName != student.lastName) {
                delete newNode;
                throw std::invalid_argument("Invalid record");
            }
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
        }
    }

    delete newNode;
    throw std::invalid_argument("Invalid record");
}

void importStudentsInCourse(
    char **inputs, char **dropDownItems, const std::string &course
) {
    int curLine = 1;
    StudentCourse studentCourse;
    Student student;
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;
    std::string *courseIDAndClassName = new std::string[2], importLine;

    splitCourseToIDAndClassName(courseIDAndClassName, course);
    studentCourse.courseID = courseIDAndClassName[0];
    studentCourse.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

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
            getStudentInCourseFromLine(student, importLine);
            studentCourse.studentID = student.id;
            checkImportedStudentInCourse(
                student, GlobalVar::allData.allStudents,
                GlobalVar::allData.allStudentCourses, studentCourse
            );
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
    }

    fin.close();
    saveAllStudentCourses(GlobalVar::allData.allStudentCourses);
    showCSVErrorLines(duplicateErrors, invalidErrors, curLine);
}

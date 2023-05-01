#include "ExportStudentsInCourse.h"

#include <algorithm>

#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../OpenFile/OpenFile.h"
#include "../OperatorOverload/OperatorOverload.h"
#include "../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void exportStudentsToFile(
    const std::string &exportPath, Student *allStudentsArray, int arraySize
) {
    std::ofstream fout;
    writeFile(fout, exportPath);

    for (int i = 0; i < arraySize; ++i) {
        Student student = allStudentsArray[i];
        fout << i + 1 << ',';
        fout << student.id << ',';
        fout << student.firstName << ',';
        fout << student.lastName << ',';
        fout << student.gender << ',';
        fout << student.dateOfBirth << ',';
        fout << student.socialID << ',';
        fout << student.className << '\n';
    }

    fout.close();
}

void exportStudentsInCourse(char **inputs, const std::string &course) {
    std::string *courseIDAndClassName = new std::string[2], exportPath = inputs[0];
    splitCourseToIDAndClassName(courseIDAndClassName, course);
    Course curCourse;
    curCourse.id = courseIDAndClassName[0];
    curCourse.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

    Node<Student> *allStudentsInCourse = getAllStudentsInCourse(curCourse);
    int arraySize;
    Student *allStudentsArray;
    transformLinkedListToArray(allStudentsInCourse, allStudentsArray, arraySize);
    std::sort(allStudentsArray, allStudentsArray + arraySize);

    if (!allStudentsInCourse) {
        throw std::invalid_argument("There's no student in this course!");
    }

    if (exportPath.back() != '\\' && exportPath.back() != '/') {
        exportPath += exportPath.find('\\') != std::string::npos ? '\\' : '/';
    }

    exportPath += "StudentsInCourse.csv";
    exportStudentsToFile(exportPath, allStudentsArray, arraySize);
    delete[] allStudentsArray;
    deleteLinkedList(allStudentsInCourse);
}

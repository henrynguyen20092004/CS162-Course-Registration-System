#include "ExportStudentsInCourse.h"

#include "../../Struct/Data.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../OpenFile/OpenFile.h"
#include "../SortAndOutputStudents/SortAndOutputStudents.h"
#include "../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void exportStudentsToFile(std::ostream &out, Student *allStudentsArray, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        Student student = allStudentsArray[i];
        out << i + 1 << ',';
        out << student.id << ',';
        out << student.firstName << ',';
        out << student.lastName << ',';
        out << student.gender << ',';
        out << student.dateOfBirth << ',';
        out << student.socialID << ',';
        out << student.className << '\n';
    }
}

void exportStudentsInCourse(char **inputs, char **dropDownItems) {
    std::string *courseIDAndClassName = new std::string[2], exportPath = inputs[0];
    splitCourseToIDAndClassName(courseIDAndClassName, dropDownItems[0]);

    Course course;
    course.id = courseIDAndClassName[0];
    course.className = courseIDAndClassName[1];
    Node<Student> *allStudentsInCourse = getAllStudentsInCourse(course);

    if (!allStudentsInCourse) {
        throw std::invalid_argument("There's no student in this course!");
    }

    if (exportPath == "") {
        throw std::invalid_argument(
            "Please enter a path to the folder you want to export!"
        );
    }

    if (exportPath.back() != '\\' && exportPath.back() != '/') {
        exportPath += exportPath.find('\\') != std::string::npos ? '\\' : '/';
    }

    exportPath += "StudentsInCourse.csv";
    std::ofstream fout;
    writeFile(fout, exportPath);
    sortAndOutputStudents(fout, allStudentsInCourse, &exportStudentsToFile);
    fout.close();
    delete[] courseIDAndClassName;
}

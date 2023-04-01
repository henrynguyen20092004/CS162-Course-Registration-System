#include "ExportStudentsInCourse.h"

#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../InputAndValidateCourse/InputAndValidateCourse.h"
#include "../OpenFile/OpenFile.h"
#include "../SortAndOutputStudents/SortAndOutputStudents.h"

void exportStudentsToFile(std::ostream &out, Student *allStudentsArray, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        Student student = allStudentsArray[i];
        out << i + 1 << ",";
        out << student.id << ",";
        out << student.firstName << ",";
        out << student.lastName << ",";
        out << student.gender << ",";
        out << student.dateOfBirth << ",";
        out << student.socialID << ",";
        out << student.className << '\n';
    }
}

void exportStudentsInCourse() {
    Course course;
    Node<Course> *allCourses = getAllCourses();
    bool validCourse = false, validPath = false;
    std::string exportPath;

    do {
        try {
            inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allCourses, course, false);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    Node<Student> *allStudentsInCourse = getAllStudentsInCourse(course);

    if (!allStudentsInCourse) {
        std::cout << "There's no student in this course, please add some!\n";
        return;
    }

    do {
        try {
            std::cout << "Please enter the path to the CSV: ";
            getline(std::cin, exportPath);

            if (exportPath == "") {
                std::cout << "Please enter a path to the folder you want to export: \n";
                continue;
            }

            if (exportPath.back() != '\\' && exportPath.back() != '/') {
                exportPath += exportPath.find('\\') != std::string::npos ? '\\' : '/';
            }

            exportPath += "StudentsInCourse.csv";
            std::ofstream fout;
            writeFile(fout, exportPath);
            sortAndOutputStudents(fout, allStudentsInCourse, &exportStudentsToFile);
            fout.close();
            validPath = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    deleteLinkedList(allCourses);
    deleteLinkedList(allStudentsInCourse);
    std::cout << "Student's info successfully exported to " << exportPath << '\n';
}

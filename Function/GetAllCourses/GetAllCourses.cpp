#include "GetAllCourses.h"

#include "../OpenFile/OpenFile.h"

Node<Course> *getAllCourse() {
    std::ifstream fin;
    readFile(fin, "Data/Course.txt");
    Course course;
    Node<Course> *cur = nullptr, *allCourse = nullptr;
    std::string tmpSemesterNumber, tmpCredits, tmpMaximumStudent, tmpSessionNumber;

    while (fin.good()) {
        getline(fin, course.schoolYearName);

        if (course.schoolYearName == "") {
            break;
        }

        getline(fin, tmpSemesterNumber);
        course.semesterNumber = stoi(tmpSemesterNumber);
        getline(fin, course.id);
        getline(fin, course.name);
        getline(fin, course.className);
        getline(fin, course.teacherName);
        getline(fin, tmpCredits);
        course.credits = stoi(tmpCredits);
        getline(fin, tmpMaximumStudent);
        course.maxStudent = stoi(tmpMaximumStudent);
        getline(fin, course.dayOfWeek);
        getline(fin, tmpSessionNumber);
        course.sessionNumber = stoi(tmpSessionNumber);

        Node<Course> *newCourse = new Node(course);

        if (!allCourse) {
            allCourse = newCourse;
            cur = allCourse;
        } else {
            cur->next = newCourse;
            cur = cur->next;
        }
    }

    fin.close();
    return allCourse;
}

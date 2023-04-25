#include "GetAllCourses.h"

void readCourse(std::ifstream &fin, Course &course) {
    getline(fin, course.schoolYearName);

    if (!fin.good()) {
        return;
    }

    std::string semesterNumber, credits, maxStudent, sessionNumber;
    getline(fin, semesterNumber);
    getline(fin, course.id);
    getline(fin, course.name);
    getline(fin, course.className);
    getline(fin, course.teacherName);
    getline(fin, credits);
    getline(fin, maxStudent);
    getline(fin, course.dayOfWeek);
    getline(fin, sessionNumber);
    course.semesterNumber = stoi(semesterNumber);
    course.credits = stoi(credits);
    course.maxStudent = stoi(maxStudent);
    course.sessionNumber = stoi(sessionNumber);
}

Node<Course> *getAllCourses() { return getAll("Data/Course.txt", &readCourse); }

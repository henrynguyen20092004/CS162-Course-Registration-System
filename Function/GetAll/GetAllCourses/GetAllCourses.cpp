#include "GetAllCourses.h"

void readCourse(std::ifstream &fin, Course &course) {
    std::string tmpSemesterNumber, tmpCredits, tmpMaximumStudent, tmpSessionNumber;
    getline(fin, course.schoolYearName);

    if (!fin.good()) {
        return;
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
}

Node<Course> *getAllCourses() {
    return getAll("Data/Course.txt", &readCourse);
}

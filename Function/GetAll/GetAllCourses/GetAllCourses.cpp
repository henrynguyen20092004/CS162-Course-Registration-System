#include "GetAllCourses.h"

#include "../../Input/Input.h"

void readCourse(std::ifstream &fin, Course &course) {
    getline(fin, course.schoolYearName);

    if (!fin.good()) {
        return;
    }

    course.semesterNumber = intInput(fin);
    getline(fin, course.id);
    getline(fin, course.name);
    getline(fin, course.className);
    getline(fin, course.teacherName);
    course.credits = intInput(fin);
    course.maxStudent = intInput(fin);
    getline(fin, course.dayOfWeek);
    course.sessionNumber = intInput(fin);
}

Node<Course> *getAllCourses() {
    return getAll("Data/Course.txt", &readCourse);
}

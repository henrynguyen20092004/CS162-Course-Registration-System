#include "GetAllCourses.h"

#include "../../../GlobalVar/GlobalVar.h"

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

Node<Course> *getAllCoursesOfThisSemester() {
    Node<Course> *allCourseOfSemester = nullptr, *curCourse;

    for (Node<Course> *cur = GlobalVar::allData.allCourses; cur; cur = cur->next) {
        Course course = cur->data;

        if (course.schoolYearName == GlobalVar::currentSemester.schoolYearName &&
            course.semesterNumber == GlobalVar::currentSemester.number) {
            pushToEndOfLinkedList(allCourseOfSemester, curCourse, course);
        }
    }

    return allCourseOfSemester;
}

Node<StudentCourse> *getAllCoursesIDOfStudent(const std::string &studentID) {
    std::ifstream fin;
    readFile(fin, "Data/StudentCourse.txt");

    Node<StudentCourse> *allCoursesIDOfStudent = nullptr, *cur;
    StudentCourse studentCourse;

    while (fin.good()) {
        getline(fin, studentCourse.studentID);

        if (!fin.good()) {
            break;
        }

        getline(fin, studentCourse.courseID);
        getline(fin, studentCourse.className);

        if (studentCourse.studentID != studentID) {
            continue;
        }

        pushToEndOfLinkedList(allCoursesIDOfStudent, cur, studentCourse);
    }

    fin.close();
    return allCoursesIDOfStudent;
}

Node<Course> *getAllCoursesOfStudent(
    const std::string &studentID, const Semester &semester
) {
    if (semester.schoolYearName == "") {
        return nullptr;
    }

    Node<StudentCourse> *allCoursesIDOfStudent = getAllCoursesIDOfStudent(studentID);
    StudentCourse tmpStudentCourse;
    Course tmpCourse;
    Node<Course> *allCoursesOfStudent = nullptr, *curCoursesOfStudent;

    for (Node<StudentCourse> *curCourseID = allCoursesIDOfStudent; curCourseID;
         curCourseID = curCourseID->next) {
        tmpStudentCourse = curCourseID->data;

        for (Node<Course> *curCourse = GlobalVar::allData.allCourses; curCourse;
             curCourse = curCourse->next) {
            tmpCourse = curCourse->data;

            if (tmpCourse.id == tmpStudentCourse.courseID &&
                tmpCourse.className == tmpStudentCourse.className &&
                tmpCourse.schoolYearName == semester.schoolYearName &&
                tmpCourse.semesterNumber == semester.number) {
                pushToEndOfLinkedList(
                    allCoursesOfStudent, curCoursesOfStudent, tmpCourse
                );
            }
        }
    }

    deleteLinkedList(allCoursesIDOfStudent);
    return allCoursesOfStudent;
}

bool listHasCourse(Node<std::string> *allCourses, const std::string &fullCourseName) {
    for (; allCourses; allCourses = allCourses->next) {
        if (allCourses->data == fullCourseName) {
            return true;
        }
    }

    return false;
}

bool isCourseInSemester(const StudentCourse &studentCourse) {
    for (Node<Course> *cur = GlobalVar::allData.allCourses; cur; cur = cur->next) {
        Course course = cur->data;

        if (course.id == studentCourse.courseID &&
            course.className == studentCourse.className &&
            course.schoolYearName == GlobalVar::currentSemester.schoolYearName &&
            course.semesterNumber == GlobalVar::currentSemester.number) {
            return true;
        }
    }

    return false;
}

Node<std::string> *getAllCoursesInClassThisSemester(Node<Score> *allScoresOfClass) {
    Node<std::string> *allCoursesInClassThisSemester = nullptr, *cur;

    for (; allScoresOfClass; allScoresOfClass = allScoresOfClass->next) {
        std::string fullCourseName = allScoresOfClass->data.studentCourse.courseID + "-" +
                                     allScoresOfClass->data.studentCourse.className;

        if (!listHasCourse(allCoursesInClassThisSemester, fullCourseName) &&
            isCourseInSemester(allScoresOfClass->data.studentCourse)) {
            pushToEndOfLinkedList(allCoursesInClassThisSemester, cur, fullCourseName);
        }
    }

    return allCoursesInClassThisSemester;
}

int getCourseCredits(const StudentCourse &studentCourse) {
    for (Node<Course> *cur = GlobalVar::allData.allCourses; cur; cur = cur->next) {
        if (cur->data.id == studentCourse.courseID &&
            cur->data.className == studentCourse.className) {
            return cur->data.credits;
        }
    }

    return 0;
}

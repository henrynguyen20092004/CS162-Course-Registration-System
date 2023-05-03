#include "SaveCourse.h"

#include "../../OpenFile/OpenFile.h"

void saveAllCourses(Node<Course> *allCourses) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt");

    for (; allCourses; allCourses = allCourses->next) {
        Course course = allCourses->data;
        fout << course.schoolYearName << '\n';
        fout << course.semesterNumber << '\n';
        fout << course.id << '\n';
        fout << course.name << '\n';
        fout << course.className << '\n';
        fout << course.teacherName << '\n';
        fout << course.credits << '\n';
        fout << course.maxStudent << '\n';
        fout << course.dayOfWeek << '\n';
        fout << course.sessionNumber << '\n';
    }

    fout.close();
}

void saveAllStudentCourses(Node<StudentCourse> *allStudentCourses) {
    std::ofstream fout;
    writeFile(fout, "Data/StudentCourse.txt");

    for (; allStudentCourses; allStudentCourses = allStudentCourses->next) {
        StudentCourse studentCourse = allStudentCourses->data;
        fout << studentCourse.studentID << '\n';
        fout << studentCourse.courseID << '\n';
        fout << studentCourse.className << '\n';
    }

    fout.close();
}

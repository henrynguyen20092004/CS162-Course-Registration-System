#include "SaveCourse.h"

#include "../OpenFile/OpenFile.h"

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

void saveAllStudent_Courses(Node<Student_Course> *allStudent_Courses) {
    std::ofstream fout;
    writeFile(fout, "Data/Student_Course.txt");

    for (; allStudent_Courses; allStudent_Courses = allStudent_Courses->next) {
        Student_Course student_course = allStudent_Courses->data;
        fout << student_course.studentID << '\n';
        fout << student_course.courseID << '\n';
        fout << student_course.className << '\n';
    }

    fout.close();
}

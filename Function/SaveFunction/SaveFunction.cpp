#include "SaveFunction.h"

#include "../../Function/OpenFile/OpenFile.h"

void saveAllCourses(Node<Course> *allCourses) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt");

    for (; allCourses; allCourses = allCourses->next) {
        fout << allCourses->data.schoolYearName << '\n';
        fout << allCourses->data.semesterNumber << '\n';
        fout << allCourses->data.id << '\n';
        fout << allCourses->data.name << '\n';
        fout << allCourses->data.className << '\n';
        fout << allCourses->data.teacherName << '\n';
        fout << allCourses->data.credits << '\n';
        fout << allCourses->data.maxStudent << '\n';
        fout << allCourses->data.dayOfWeek << '\n';
        fout << allCourses->data.sessionNumber << '\n';
    }

    fout.close();
}

void saveAllStudent_Course_Class(Node<Student_Course_Class> *allStudent_Course) {
    std::ofstream fout;
    writeFile(fout, "Data/Student_Course_Class.txt");

    for (; allStudent_Course; allStudent_Course = allStudent_Course->next) {
        fout << allStudent_Course->data.studentID << '\n';
        fout << allStudent_Course->data.courseID << '_'
             << allStudent_Course->data.className << '\n';
    }

    fout.close();
}

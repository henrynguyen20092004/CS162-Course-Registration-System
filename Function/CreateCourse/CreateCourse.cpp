#include "CreateCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../CreateSemester/CreateSemester.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../Input/Input.h"
#include "../InputAndValidateCourse/InputAndValidateCourse.h"

void validateCourse(
    Node<Course> *allCourses, const Course &course
) {
    validateCourseIDAndClass(allCourses, course, true);
    validateOtherCourseInformation(course);
}

void inputCourse(Course &course) {
    inputCourseIDAndClassName(course);
    inputOtherCourseInformation(course);
}

void saveCourse(const Course &course) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt", std::ios::app);
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
    fout.close();
}

void createCourse(const Semester &semester) {
    if (semester.schoolYearName == "") {
        std::cout << "Please create a semester first!\n";
        return;
    }

    Node<Course> *allCourses = getAllCourses();
    Course course;
    bool validCourse = false;
    course.schoolYearName = semester.schoolYearName;
    course.semesterNumber = semester.number;

    do {
        try {
            inputCourse(course);
            validateCourse(allCourses, course);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    saveCourse(course);
    deleteLinkedList(allCourses);
    std::cout << "Course successfully added!\n";
}

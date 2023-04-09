#include "CreateCourse.h"

#include <cstring>

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../DateFunction/DateFunction.h"
#include "../../Input/Input.h"
#include "../../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../CreateSemester/CreateSemester.h"

void validateCourse(Node<Course> *allCourses, const Course &course) {
    validateCourseIDAndClass(allCourses, course, true);
    validateOtherCourseInformation(course);
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
    addNewItemsToOldList(allData.allCourses, new Node(course));
}

int convertStringToInteger(char *&str) {
    int res{0};

    for (int i = 0; i < strlen(str); ++i) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}

void createCourse(
    const Semester &semester, char *&courseID, char *&className, char *&courseName,
    char *&teacherName, char *&credits, char *&maxStudent, char *&dayOfWeek,
    char *&sessionNumber
) {
    if (semester.schoolYearName == "") {
        throw std::runtime_error("Please create a semester first!");
    }

    Course course;
    course.schoolYearName = semester.schoolYearName;
    course.semesterNumber = semester.number;

    course.id = courseID;
    course.className = className;
    course.name = courseName;
    course.teacherName = teacherName;
    course.credits = convertStringToInteger(credits);
    course.maxStudent = convertStringToInteger(maxStudent);
    course.dayOfWeek = dayOfWeek;
    course.sessionNumber = convertStringToInteger(sessionNumber);

    validateCourse(allData.allCourses, course);
    saveCourse(course);
}

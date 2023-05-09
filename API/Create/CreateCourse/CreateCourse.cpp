#include "CreateCourse.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../ValidateCourse/ValidateCourse.h"

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
    addNewItemsToOldList(GlobalVar::allData.allCourses, new Node(course));
}

void createCourse(char **inputs, char **dropDownItems) {
    Course course;

    course.schoolYearName = GlobalVar::currentSemester.schoolYearName;
    course.semesterNumber = GlobalVar::currentSemester.number;
    course.id = inputs[0];
    course.className = inputs[1];
    course.name = inputs[2];
    course.teacherName = checkAndConvertToName(inputs[3], "teacher name");
    course.credits = checkAndConvertToInt(inputs[4], "credits");
    course.maxStudent = checkAndConvertToInt(inputs[5], "max student");
    course.dayOfWeek = dropDownItems[0];
    course.sessionNumber = stoi(std::string(dropDownItems[1]));

    if (checkCourseExists(GlobalVar::allData.allCourses, course.id, course.className)) {
        throw std::invalid_argument("This course already exists, please try again!");
    }

    if (!checkClassExists(GlobalVar::allData.allClasses, course.className)) {
        throw std::invalid_argument("This class does not exist, please try again!");
    }

    validateCourse(course);
    saveCourse(course);
}

#include "CreateCourse.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../DateFunction/DateFunction.h"
#include "../../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"

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

void createCourse(const Semester &semester, char **inputs, char **dropDownItems) {
    if (semester.schoolYearName == "") {
        throw std::runtime_error("Please create a semester first!");
    }

    Course course;
    course.schoolYearName = semester.schoolYearName;
    course.semesterNumber = semester.number;
    course.id = inputs[0];
    course.className = inputs[1];
    course.name = inputs[2];
    course.teacherName = checkAndConvertToName(inputs[3], "teacher name");
    course.credits = checkAndConvertToInt(inputs[4], "credits");
    course.maxStudent = checkAndConvertToInt(inputs[5], "max student");
    course.dayOfWeek = dropDownItems[0];
    course.sessionNumber = stoi(std::string(dropDownItems[1]));

    if (checkCourseExists(allData.allCourses, course.id, course.className)) {
        throw std::invalid_argument("This course already exists, please try again!");
    }

    validateOtherCourseInformation(course);
    saveCourse(course);
}

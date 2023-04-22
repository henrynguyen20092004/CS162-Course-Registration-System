#include "UpdateCourse.h"

#include "../../../Struct/Data.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../../Save/SaveCourse/SaveCourse.h"
#include "../../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void inputChanges(Course& course, char** inputs, char** dropDownItems) {
    std::string* courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, dropDownItems[0]);

    try {
        course.id = courseIDAndClassName[0];
        course.className = courseIDAndClassName[1];
        course.name = inputs[0];
        course.teacherName = checkAndConvertToName(inputs[1], "teacher name");
        course.credits = checkAndConvertToInt(inputs[2], "credit");
        course.maxStudent = checkAndConvertToInt(inputs[3], "number of students");
        course.dayOfWeek = dropDownItems[1];
        course.sessionNumber =
            stoi(checkDropDownAndConvertToString(dropDownItems[2], "session number"));
        delete[] courseIDAndClassName;
    } catch (...) {
        delete[] courseIDAndClassName;
        throw;
    }
}

void updateCourse(char** inputs, char** dropDownItems) {
    if (!allData.allCourses) {
        throw std::invalid_argument(
            "No course records, please create one and try again later!"
        );
    }

    Course course;
    inputChanges(course, inputs, dropDownItems);
    validateOtherCourseInformation(course);

    for (Node<Course>* cur = allData.allCourses; cur; cur = cur->next) {
        Course curCourse = cur->data;

        if (course.id == curCourse.id && course.className == curCourse.className) {
            course.schoolYearName = curCourse.schoolYearName;
            course.semesterNumber = curCourse.semesterNumber;
            cur->data = course;
            break;
        }
    }

    saveAllCourses(allData.allCourses);
}

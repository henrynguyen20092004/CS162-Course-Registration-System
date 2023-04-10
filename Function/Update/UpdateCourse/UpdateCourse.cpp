#include "UpdateCourse.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../../Save/SaveCourse/SaveCourse.h"
#include "../../View/ViewCourses/ViewCourses.h"

void inputChanges(Course& course, char** inputs) {
    course.id = inputs[0];
    course.className = inputs[1];
    course.name = checkNameAndConvertToName(inputs[2], "course name");
    course.teacherName = checkNameAndConvertToName(inputs[3], "teacher name");
    course.credits = checkAndConvertToInt(inputs[4], "credit");
    course.maxStudent = checkAndConvertToInt(inputs[5], "number of students");
    course.dayOfWeek = inputs[6];
    course.sessionNumber = checkAndConvertToInt(inputs[7], "session number");
}

void updateCourse(char** inputs) {
    if (!allData.allCourses) {
        throw std::invalid_argument(
            "No course records, please create one and try again later!"
        );
    }

    Course course;
    inputChanges(course, inputs);
    validateCourseIDAndClass(allData.allCourses, course, false);
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

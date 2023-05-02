#include "UpdateCourse.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../Save/SaveCourse/SaveCourse.h"
#include "../../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"
#include "../../ValidateCourse/ValidateCourse.h"

void inputChanges(Course& course, char** inputs, char** dropDownItems) {
    std::string* courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, dropDownItems[0]);
    course.id = courseIDAndClassName[0];
    course.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

    course.name = inputs[0];
    course.teacherName = checkAndConvertToName(inputs[1], "teacher name");
    course.credits = checkAndConvertToInt(inputs[2], "credit");
    course.maxStudent = checkAndConvertToInt(inputs[3], "number of students");
    course.dayOfWeek = dropDownItems[1];
    course.sessionNumber = stoi(std::string(dropDownItems[2]));
}

void updateCourse(char** inputs, char** dropDownItems) {
    Course course;
    inputChanges(course, inputs, dropDownItems);
    validateCourse(course);

    for (Node<Course>* cur = GlobalVar::allData.allCourses; cur; cur = cur->next) {
        Course curCourse = cur->data;

        if (course.id == curCourse.id && course.className == curCourse.className) {
            course.schoolYearName = curCourse.schoolYearName;
            course.semesterNumber = curCourse.semesterNumber;
            cur->data = course;
            break;
        }
    }

    saveAllCourses(GlobalVar::allData.allCourses);
}

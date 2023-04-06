#include "UpdateCourse.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../../Save/SaveCourse/SaveCourse.h"
#include "../../View/ViewCourses/ViewCourses.h"

void inputChanges(Course &course) {
    bool validCourse = false;

    do {
        try {
            inputOtherCourseInformation(course);
            validateOtherCourseInformation(course);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);
}

void updateCourse() {
    if (!allData.allCourses) {
        std::cout << "No course records, please create one and try again later!\n";
        return;
    }

    bool validCourse = false;
    Course course;

    do {
        try {
            inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allData.allCourses, course, false);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    for (Node<Course> *cur = allData.allCourses; cur; cur = cur->next) {
        Course curCourse = cur->data;

        if (course.id == curCourse.id && course.className == curCourse.className) {
            std::cout << "\nThis is the current information of this course:\n";
            viewACourse(curCourse);
            std::cout << "Please enter new information for this course:\n";
            inputChanges(cur->data);
            break;
        }
    }

    saveAllCourses(allData.allCourses);
    std::cout << "Course successfully updated!\n";
}

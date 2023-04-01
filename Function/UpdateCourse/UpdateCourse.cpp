#include "UpdateCourse.h"

#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../InputAndValidateCourse/InputAndValidateCourse.h"
#include "../SaveCourse/SaveCourse.h"
#include "../ViewCourses/ViewCourses.h"

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
    Node<Course> *allCourses = getAllCourses(), *cur = allCourses;

    if (!allCourses) {
        std::cout << "No course records, please create one and try again later!\n";
        return;
    }

    bool validCourse = false;
    Course course;

    do {
        try {
            inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allCourses, course, false);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    for (; cur; cur = cur->next) {
        Course curCourse = cur->data;

        if (course.id == curCourse.id && course.className == curCourse.className) {
            std::cout << "\nThis is the current information of this course:\n";
            viewACourse(curCourse);
            std::cout << "Please enter new information for this course:\n";
            inputChanges(cur->data);
            break;
        }
    }

    saveAllCourses(allCourses);
    deleteLinkedList(allCourses);
    std::cout << "Course successfully updated!\n";
}

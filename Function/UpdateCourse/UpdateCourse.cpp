#include "UpdateCourse.h"

#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../InputCourse/InputCourse.h"
#include "../SaveCourse/SaveCourse.h"
#include "../ValidateCourse/ValidateCourse.h"
#include "../ViewCourses/ViewCourses.h"

void inputChanges(Course &course) {
    bool validCourse = false;

    do {
        try {
            inputOtherInformation(course);
            validateOtherInformation(course);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);
}

void updateCourse() {
    Node<Course> *allCourses = getAllCourses(), *cur = allCourses;

    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }

    bool courseExists;
    Course course;

    do {
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!courseExists);

    for (; cur; cur = cur->next) {
        Course curCourse = cur->data;

        if (course.id == curCourse.id && course.className == curCourse.className) {
            std::cout << "\nThis is the current information of this course:\n";
            viewACourse(curCourse);
            std::cout << "Please enter new information for this course:\n";
            inputChanges(curCourse);
            std::cout << "Course successfully updated!\n";
            break;
        }
    }

    saveAllCourses(allCourses);
    deleteLinkedList(allCourses);
}

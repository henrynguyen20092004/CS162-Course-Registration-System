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

    bool courseExists = false;
    Course course;

    do {
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!courseExists);

    while (cur) {
        if (course.id == cur->data.id && course.className == cur->data.className) {
            std::cout << "\nThis is the current information of this course:\n";
            viewACourse(cur->data);

            std::cout << "Please enter new information for this course:\n";
            inputChanges(cur->data);

            std::cout << "Course successfully updated!\n";
            break;
        }

        cur = cur->next;
    }

    saveAllCourses(allCourses);
    deleteLinkedList(allCourses);
}

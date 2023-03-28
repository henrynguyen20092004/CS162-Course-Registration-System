#include "UpdateCourse.h"

#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../InputCourse/InputCourse.h"
#include "../SaveCourse/SaveCourse.h"
#include "../UpdateCourse/UpdateCourse.h"
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
    Node<Course> *allCourses = getAllCourses(), *cur;

    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }

    bool stopFlag = false;
    Course course;
    std::string id, className;

    do {
        inputCourseIDAndClassName(course);
        cur = allCourses;

        while (cur) {
            if (course.id == cur->data.id && course.className == cur->data.className) {
                std::cout << "\nCourse found! This is the current information of this "
                             "course:\n\n";
                viewACourse(cur->data);

                std::cout << "Please enter new information for this course:\n";
                inputChanges(cur->data);

                std::cout << "Course successfully updated!\n";
                stopFlag = true;
                break;
            } else {
                cur = cur->next;
            }
        }

        if (!stopFlag) {
            std::cout << "No such course found! Please try again!\n";
        }
    } while (!stopFlag);

    saveAllCourses(allCourses);
    deleteLinkedList(allCourses);
}

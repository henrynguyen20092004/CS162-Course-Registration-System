#include "DeleteCourse.h"

#include "../../Struct/Data.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../Save/SaveCourse/SaveCourse.h"

void deleteAllStudentsInCourse(const std::string &id, const std::string &className) {
    Node<StudentCourse> *allStudentCourses = new Node(allData.allStudentCourses),
                        *cur = allStudentCourses, *tmpStudentCourse;

    while (cur->next) {
        if (cur->next->data.courseID == id && cur->next->data.className == className) {
            tmpStudentCourse = cur->next;
            cur->next = tmpStudentCourse->next;
            delete tmpStudentCourse;
        } else {
            cur = cur->next;
        }
    }

    allData.allStudentCourses = allStudentCourses->next;
    saveAllStudentCourses(allData.allStudentCourses);
    delete allStudentCourses;
}

void deleteCourse() {
    if (!allData.allCourses) {
        std::cout << "No course records, please create one and try again!\n";
        return;
    }

    Node<Course> *allCourses = new Node(allData.allCourses), *cur = allCourses,
                 *tmpCourse;

    Course course;
    bool validCourse = false;

    do {
        try {
            inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allCourses, course, false);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    for (; cur->next; cur = cur->next) {
        tmpCourse = cur->next;

        if (course.id == tmpCourse->data.id &&
            course.className == tmpCourse->data.className) {
            deleteAllStudentsInCourse(course.id, course.className);
            cur->next = tmpCourse->next;
            delete tmpCourse;
            break;
        }
    }

    allData.allCourses = allCourses->next;
    saveAllCourses(allData.allCourses);
    delete allCourses;
    std::cout << "Course successfully deleted!\n";
}

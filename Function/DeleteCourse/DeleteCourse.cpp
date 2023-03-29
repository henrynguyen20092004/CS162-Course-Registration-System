#include "DeleteCourse.h"

#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputCourse/InputCourse.h"
#include "../SaveCourse/SaveCourse.h"

void deleteAllStudentsInCourse(const std::string &id, const std::string &className) {
    Node<Student_Course> *allStudent_Course = new Node(getAllStudent_Courses()),
                         *cur = allStudent_Course, *tempStudent_Course;

    while (cur->next) {
        if (cur->next->data.courseID == id && cur->next->data.className == className) {
            tempStudent_Course = cur->next;
            cur->next = cur->next->next;
            delete tempStudent_Course;
        }

        cur = cur->next;
    }

    saveAllStudent_Course(allStudent_Course->next);
    deleteLinkedList(allStudent_Course);
}

void deleteCourse() {
    Node<Course> *allCourses = new Node(getAllCourses()), *cur = allCourses, *tmpCourse;

    if (!allCourses->next) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        deleteLinkedList(allCourses);
        return;
    }

    Course course;
    bool courseExists = false;

    do {
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!courseExists);

    while (cur->next) {
        if (course.id == cur->next->data.id &&
            course.className == cur->next->data.className) {
            deleteAllStudentsInCourse(course.id, course.className);

            tmpCourse = cur->next;
            cur->next = cur->next->next;
            delete tmpCourse;

            std::cout << "Course successfully deleted!\n";
            break;
        }

        cur = cur->next;
    }

    saveAllCourses(allCourses->next);
    deleteLinkedList(allCourses);
}

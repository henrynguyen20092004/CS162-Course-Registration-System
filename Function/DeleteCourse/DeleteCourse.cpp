#include "DeleteCourse.h"

#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputCourse/InputCourse.h"
#include "../SaveCourse/SaveCourse.h"

void deleteAllStudentsInCourse(const std::string &id, const std::string &className) {
    Node<Student_Course> *allStudent_Courses = new Node(getAllStudent_Courses()),
                         *cur = allStudent_Courses, *tmpStudent_Course;

    while (cur->next) {
        if (cur->next->data.courseID == id && cur->next->data.className == className) {
            tmpStudent_Course = cur->next;
            cur->next = tmpStudent_Course->next;
            delete tmpStudent_Course;
        } else {
            cur = cur->next;
        }
    }

    saveAllStudent_Courses(allStudent_Courses->next);
    deleteLinkedList(allStudent_Courses);
}

void deleteCourse() {
    Node<Course> *allCourses = new Node(getAllCourses()), *cur = allCourses, *tmpCourse;

    if (!allCourses->next) {
        std::cout << "No course records, please create one and try again later!\n";
        deleteLinkedList(allCourses);
        return;
    }

    Course course;
    bool courseExists;

    do {
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!courseExists);

    for (; cur->next; cur = cur->next) {
        tmpCourse = cur->next;

        if (course.id == tmpCourse->data.id &&
            course.className == tmpCourse->data.className) {
            deleteAllStudentsInCourse(course.id, course.className);
            cur->next = tmpCourse->next;
            delete tmpCourse;
            std::cout << "Course successfully deleted!\n";
            break;
        }
    }

    saveAllCourses(allCourses->next);
    deleteLinkedList(allCourses);
}

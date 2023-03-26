#include "DeleteCourse.h"

#include "../GetAllCourses/GetAllCourses.h"
#include "../GetAllStudents/GetAllStudents.h"
#include "../OpenFile/OpenFile.h"
#include "../SaveCourse/SaveCourse.h"

void inputCourseIDAndClassName(std::string &id, std::string &className) {
    std::cout << "Please enter the course's id: ";
    getline(std::cin, id);
    std::cout << "Please the course's class: ";
    getline(std::cin, className);
}

void deleteAllStudentsInCourse(const std::string &id, const std::string &className) {
    Node<Student_Course> *allStudent_Course = new Node<Student_Course>,
                         *cur = allStudent_Course, *tempStudent_Course;
    allStudent_Course->next = getAllStudent_Course();

    while (cur->next) {
        if (cur->next->data.courseID == id && cur->next->data.className == className) {
            tempStudent_Course = cur->next;
            cur->next = cur->next->next;
            delete tempStudent_Course;
        } else {
            cur = cur->next;
        }
    }

    saveAllStudent_Course(allStudent_Course->next);
    deleteLinkedList(allStudent_Course);
}

void deleteCourse() {
    Node<Course> *allCourses = new Node<Course>, *cur = allCourses, *tmpCourse;
    allCourses->next = getAllCourse();

    if (!allCourses->next) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        deleteLinkedList(allCourses);
        return;
    }

    std::string id, className;
    bool stopFlag = false;

    do {
        inputCourseIDAndClassName(id, className);

        while (cur->next) {
            if (id == cur->next->data.id && className == cur->next->data.className) {
                deleteAllStudentsInCourse(id, className);

                tmpCourse = cur->next;
                cur->next = cur->next->next;
                delete tmpCourse;

                std::cout << "Course successfully deleted!\n";
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

    saveAllCourses(allCourses->next);
    deleteLinkedList(allCourses);
}

#include "UpdateCourseInformation.h"

#include "../../Function/Check/CheckClass/CheckClass.h"
#include "../../Function/Check/CheckCourse/CheckCourse.h"
#include "../../Function/CreateCourse/CreateCourse.h"
#include "../../Function/GetAll/GetAllClasses/GetAllClasses.h"
#include "../../Function/GetAll/GetAllCourses/GetAllCourses.h"
#include "../../Function/GetAll/GetAllSemesters/GetAllSemesters.h"
#include "../../Function/Input/Input.h"
#include "../../Function/SaveCourse/SaveCourse.h"
#include "../../Function/UpdateCourseInformation/UpdateCourseInformation.h"
#include "../DateFunction/DateFunction.h"

void inputCourseKey(std::string &id, std::string &className) {
    std::cout << "Please enter the course's id: ";
    getline(std::cin, id);
    std::cout << "Please the course's class: ";
    getline(std::cin, className);
}

void displayCourseInformation(const Course &course) {
    std::cout << "School year: " << course.schoolYearName << '\n';
    std::cout << "Semester number: " << course.semesterNumber << '\n';
    std::cout << "Course id: " << course.id << '\n';
    std::cout << "Course name: " << course.name << '\n';
    std::cout << "Class name: " << course.className << '\n';
    std::cout << "Teacher name: " << course.teacherName << '\n';
    std::cout << "Credits: " << course.credits << '\n';
    std::cout << "Maximum number of students: " << course.maxStudent << '\n';
    std::cout << "Day of week that the course is performed: " << course.dayOfWeek << '\n';
    std::cout << "The session that the course is performed: Session "
              << course.sessionNumber << "\n\n";
}

void validateCourse(const Course &course) {
    if (course.credits < 1) {
        throw std::invalid_argument("Invalid credits number, please try again!\n");
    }

    if (course.maxStudent < 1) {
        throw std::invalid_argument(
            "Invalid maximum number of students, please try again!\n"
        );
    }

    if (!checkDayOfWeek(course.dayOfWeek)) {
        throw std::invalid_argument("Invalid day of week, please try again!\n");
    }

    if (course.sessionNumber < 1 || course.sessionNumber > 4) {
        throw std::invalid_argument("Invalid session number, please try again!\n");
    }
}

void inputNewCourseInformation(Course &course) {
    std::cout << "Please enter the course name: ";
    getline(std::cin, course.name);
    std::cout << "Please enter the teacher name: ";
    course.teacherName = nameInput();
    std::cout << "Please enter the number of credits of this course: ";
    course.credits = intInput();
    std::cout << "Please enter the maximum number of students in the course: ";
    course.maxStudent = intInput();
    std::cout << "Please choose the day of week that the course will be perfomed "
                 "(MON/TUE/WED/THU/FRI/SAT): ";
    getline(std::cin, course.dayOfWeek);
    std::cout << "Please choose the session number that the course will be perfomed: ";
    course.sessionNumber = intInput();
}

void modifyCourse(Course &course) {
    bool validCourse = false;
    do {
        try {
            inputNewCourseInformation(course);
            validateCourse(course);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);
}

void updateCourseInformation() {
    Node<Course> *allCourses = getAllCourses(), *cur = nullptr;

    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }

    bool stopFlag = false;
    Course course;
    Semester semester;
    std::string id, className;

    do {
        inputCourseKey(id, className);
        cur = allCourses;

        while (cur) {
            if (id == cur->data.id && className == cur->data.className) {
                std::cout << "Course identified! This is the current information of this "
                             "course:\n";
                displayCourseInformation(cur->data);

                std::cout << "Please enter new information for this course:\n";
                modifyCourse(cur->data);

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

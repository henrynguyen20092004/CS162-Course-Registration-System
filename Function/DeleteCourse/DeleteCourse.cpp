#include "DeleteCourse.h"

#include "../../Function/GetAllStudents/GetAllStudents.h"
#include "../../Function/OpenFile/OpenFile.h"
#include "../../Function/SaveFunction/SaveFunction.h"

// from feat/CRS-add-course-to-semester
Node<Course> *getAllCourse() {
    std::ifstream fin;
    readFile(fin, "Data/Course.txt");
    Course course;
    Node<Course> *allCourse = nullptr;
    Node<Course> *cur = nullptr;
    std::string tmpSemesterNumber, tmpCredits, tmpMaximumStudent, tmpSessionNumber;
    while (fin.good()) {
        getline(fin, course.schoolYearName);
        if (course.schoolYearName == "") {
            break;
        }
        getline(fin, tmpSemesterNumber);
        course.semesterNumber = stoi(tmpSemesterNumber);
        getline(fin, course.id);
        getline(fin, course.name);
        getline(fin, course.className);
        getline(fin, course.teacherName);
        getline(fin, tmpCredits);
        course.credits = stoi(tmpCredits);
        getline(fin, tmpMaximumStudent);
        course.maxStudent = stoi(tmpMaximumStudent);
        getline(fin, course.dayOfWeek);
        getline(fin, tmpSessionNumber);
        course.sessionNumber = stoi(tmpSessionNumber);

        Node<Course> *newCourse = new Node<Course>(course);

        if (!allCourse) {
            allCourse = newCourse;
            cur = allCourse;
        } else {
            cur->next = newCourse;
            cur = cur->next;
        }
    }
    fin.close();
    return allCourse;
}

void inputCourseIDAndClassName(std::string &id, std::string &className) {
    std::cout << "Please type in the id of the course you want to delete: ";
    getline(std::cin, id);
    std::cout << "Please specify which class you want to delete this course from: ";
    getline(std::cin, className);
}

void deleteAllStudentsInCourse(std::string &id, std::string &className) {
    Node<Student_Course_Class> *allStudent_Course_Class = new Node<Student_Course_Class>,
                               *cur = allStudent_Course_Class, *tempStudent_Course;
    allStudent_Course_Class->next = getAllStudent_Course_Class();

    while (cur->next) {
        if (cur->next->data.courseID == id && cur->next->data.className == className) {
            tempStudent_Course = cur->next;
            cur->next = cur->next->next;
            delete tempStudent_Course;
        } else {
            cur = cur->next;
        }
    }

    saveAllStudent_Course_Class(allStudent_Course_Class->next);
    deleteLinkedList(allStudent_Course_Class);
}

void deleteCourse() {
    Node<Course> *allCourses = new Node<Course>, *cur = allCourses, *tmpCourse;
    allCourses->next = getAllCourse();

    if (!allCourses->next) {
        std::cout << "There is no course at the moment! Please try again later!\n";
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
                saveAllCourses(allCourses->next);
                break;
            } else {
                cur = cur->next;
            }
        }

        if (!stopFlag) {
            std::cout << "No such course found! Please try again!\n";
        }
    } while (!stopFlag);

    deleteLinkedList(allCourses);
}

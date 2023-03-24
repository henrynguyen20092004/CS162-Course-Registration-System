#include "DeleteCourse.h"

#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

// from feat/CRS-add-course-to-semester
Node<Course> *getAllCourse() {
    Node<Course> *allCourse = nullptr;
    std::ifstream fin;
    readFile(fin, "Data/Course.txt");
    Course course;
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

        Node<Course> *newCourse = new Node(course);

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

void inputCourseIDAndClassName(std::string &ID, std::string &CourseName) {
    std::cout << "Please type in the course you want to delete: ";
    std::cin >> ID;
    std::cout << "Please specify which class you want to delete this course from: ";
    std::cin >> CourseName;
}

void saveAllCourses(Node<Course> *&allCourses) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt", std::ios::trunc);

    for (; allCourses; allCourses = allCourses->next) {
        fout << allCourses->data.schoolYearName << '\n';
        fout << allCourses->data.semesterNumber << '\n';
        fout << allCourses->data.id << '\n';
        fout << allCourses->data.name << '\n';
        fout << allCourses->data.className << '\n';
        fout << allCourses->data.teacherName << '\n';
        fout << allCourses->data.credits << '\n';
        fout << allCourses->data.maxStudent << '\n';
        fout << allCourses->data.dayOfWeek << '\n';
        fout << allCourses->data.sessionNumber << '\n';
    }

    fout.close();
}

void deleteCourse() {
    Node<Course> *allCourses = getAllCourse();
    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }

    std::string ID;
    std::string ClassName;
    Node<Course> *tmpCourse = new Node<Course>();
    tmpCourse->next = allCourses;
    allCourses = tmpCourse;

    inputCourseIDAndClassName(ID, ClassName);
    while (allCourses->next) {
        if (ID == allCourses->next->data.id &&
            ClassName == allCourses->next->data.className) {
            tmpCourse = allCourses->next;
            allCourses->next = allCourses->next->next;
            delete tmpCourse;

            saveAllCourses(allCourses);
            deleteLinkedList(allCourses);
            std::cout << "The course is deleted successfully!\n";
            return;
        }
        allCourses = allCourses->next;
    }

    std::cout << "No such course found! Please try again!\n";

    tmpCourse = allCourses;
    allCourses = allCourses->next;
    delete tmpCourse;
    deleteLinkedList(allCourses);
}
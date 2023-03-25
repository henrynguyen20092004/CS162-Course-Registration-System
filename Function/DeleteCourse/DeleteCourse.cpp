#include "DeleteCourse.h"

#include "../../Function/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

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
    std::cout
        << "Please type in the id of the course you want to delete (type 0 to stop): ";
    getline(std::cin, id);

    if (id == "0") {
        return;
    }

    std::cout << "Please specify which class you want to delete this course from: ";
    getline(std::cin, className);
}

void saveAllCourses(Node<Course> *allCourses) {
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

void saveAllStudent_Course(Node<Student_Course> *allStudent_Course) {
    std::ofstream fout;
    writeFile(fout, "Data/Student_Course.txt");

    for (; allStudent_Course; allStudent_Course = allStudent_Course->next) {
        fout << allStudent_Course->data.studentID << '\n';
        fout << allStudent_Course->data.courseID << '\n';
    }

    fout.close();
}

void deleteAllStudentsInCourse(Course &course, std::string &className) {
    Node<std::string> *allCourseStudentID = getAllStudentsIDInClass(className);
    Node<Student_Course> *allStudent_Course = new Node<Student_Course>();
    allStudent_Course->next = getAllStudent_Course();

    Node<std::string> *cur = allCourseStudentID;
    Node<Student_Course> *cur2;
    Node<Student_Course> *tempStudent_Course;

    for (; cur; cur = cur->next) {
        cur2 = allStudent_Course;
        while (cur2->next) {
            if (cur2->next->data.courseID == course.id &&
                cur2->next->data.studentID == cur->data) {
                tempStudent_Course = cur2->next;
                cur2->next = cur2->next->next;
                delete tempStudent_Course;
                break;
            } else {
                cur2 = cur2->next;
            }
        }
    }

    tempStudent_Course = allStudent_Course;
    allStudent_Course = allStudent_Course->next;
    delete tempStudent_Course;

    saveAllStudent_Course(allStudent_Course);
    deleteLinkedList(allStudent_Course);
    deleteLinkedList(allCourseStudentID);
}

void deleteCourse() {
    Node<Course> *allCourses = getAllCourse();
    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }

    std::string id;
    std::string className;
    Node<Course> *tmpCourse = new Node<Course>();
    tmpCourse->next = allCourses;
    allCourses = tmpCourse;
    Node<Course> *cur = allCourses;
    bool stopFlag = false;

    do {
        inputCourseIDAndClassName(id, className);

        if (id == "0") {
            break;
        }

        while (cur->next) {
            if (id == cur->next->data.id && className == cur->next->data.className) {
                deleteAllStudentsInCourse(cur->next->data, className);

                tmpCourse = cur->next;
                cur->next = cur->next->next;
                delete tmpCourse;

                tmpCourse = allCourses;
                allCourses = allCourses->next;
                delete tmpCourse;

                saveAllCourses(allCourses);
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

    deleteLinkedList(allCourses);
}

#include "CreateCourse.h"

#include "../../Struct/LinkedList.h"
#include "../CreateSemester/CreateSemester.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

Node<std::string> *getAllClassName() {
    Node<std::string> *allClassName = nullptr;
    std::ifstream fin;
    readFile(fin, "Data/Class.txt");
    Node<std::string> *cur = nullptr;
    std::string className;
    while (fin.good()) {
        getline(fin, className);
        if (className == "") {
            break;
        }
        if (!allClassName) {
            allClassName = new Node(className);
            cur = allClassName;
        } else {
            cur->next = new Node(className);
            cur = cur->next;
        }
    }
    fin.close();
    return allClassName;
}

bool checkClassExist(Node<std::string> *allClassName, const std::string &className) {
    while (allClassName) {
        if (allClassName->data == className) {
            return true;
        }
        allClassName = allClassName->next;
    }
    return false;
}

bool checkValidDayOfWeek(const std::string &day) {
    return day == "MON" || day == "TUE" || day == "WED" || day == "THU" || day == "FRI" ||
           day == "SAT";
}

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

bool checkCourseIDExist(Node<Course> *allCourse, const std::string &courseID) {
    while (allCourse) {
        if (allCourse->data.id == courseID) {
            return true;
        }
        allCourse = allCourse->next;
    }
    return false;
}

bool checkCourseNameExist(
    Node<Course> *allCourse, const std::string &courseName, const std::string &schoolYear
) {
    while (allCourse) {
        if (allCourse->data.schoolYearName == schoolYear &&
            allCourse->data.name == courseName) {
            return true;
        }
        allCourse = allCourse->next;
    }
    return false;
}

void inputCourse(Course &course, const Semester &semester) {
    Node<std::string> *allClassName = nullptr;
    allClassName = getAllClassName();
    Node<Course> *allCourse = nullptr;
    allCourse = getAllCourse();

    bool classNameExist, courseIDExist, courseNameExist, validTeacherName,
        validMaxStudentNumber = false, validDayOfWeek = false, validSessionNumber = false,
        validCredits = false;
    do {
        std::cout << "Please enter course id: ";
        getline(std::cin, course.id);
        courseIDExist = checkCourseIDExist(allCourse, course.id);
        if (courseIDExist) {
            std::cout << "This course already existed. Please try again!\n";
        }
    } while (courseIDExist);

    do {
        std::cout << "Please enter course name: ";
        getline(std::cin, course.name);
        courseNameExist =
            checkCourseNameExist(allCourse, course.name, semester.schoolYearName);
        if (courseNameExist) {
            std::cout << "This course already existed. Please try again!\n";
        }
    } while (courseNameExist);

    do {
        std::cout << "Please enter class name: ";
        getline(std::cin, course.className);
        classNameExist = checkClassExist(allClassName, course.className);
        if (!classNameExist) {
            std::cout << "This class does not exist. Please try again!\n";
        }
    } while (!classNameExist);

    do {
        try {
            std::cout << "Please enter teacher name: ";
            course.teacherName = nameInput();
            validTeacherName = true;
        } catch (std::exception &error) {
            std::cout << error.what();
            validTeacherName = false;
        }
    } while (!validTeacherName);

    do {
        try {
            std::cout << "Please enter number of credits: ";
            course.credits = intInput();
            validCredits = course.credits > 0 && course.credits <= INT_MAX;
            if (!validCredits) {
                std::cout << "Invalid credits number. Please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCredits);

    do {
        try {
            std::cout << "Please enter the maximum number of students in the course: ";
            course.maxStudent = intInput();
            validMaxStudentNumber = course.maxStudent >= 1 && course.maxStudent <= 50;
            if (!validMaxStudentNumber) {
                std::cout << "Your input is invalid. Please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validMaxStudentNumber);

    do {
        std::cout << "Please choose day of week that the course will be "
                     "perfomed (MON/TUE/WED/THU/FRI/SAT): ";
        getline(std::cin, course.dayOfWeek);

        for (char &x : course.dayOfWeek) {
            x = toupper(x);
        }

        validDayOfWeek = checkValidDayOfWeek(course.dayOfWeek);
        if (!validDayOfWeek) {
            std::cout << "Invalid day of week, please try again!\n";
        }
    } while (!validDayOfWeek);

    do {
        try {
            std::cout << "Please choose session number that the course will be "
                         "perfomed: ";
            course.sessionNumber = intInput();
            validSessionNumber = course.sessionNumber > 0 && course.sessionNumber <= 4;
            if (!validSessionNumber) {
                std::cout << "Invalid session number, please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validSessionNumber);

    course.semesterNumber = semester.number;
    course.schoolYearName = semester.schoolYearName;

    deleteLinkedList(allClassName);
    deleteLinkedList(allCourse);
}

void saveCourse(Course course) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt", std::ios::app);
    fout << course.schoolYearName << '\n';
    fout << course.semesterNumber << '\n';
    fout << course.id << '\n';
    fout << course.name << '\n';
    fout << course.className << '\n';
    fout << course.teacherName << '\n';
    fout << course.credits << '\n';
    fout << course.maxStudent << '\n';
    fout << course.dayOfWeek << '\n';
    fout << course.sessionNumber << '\n';
    fout.close();
}

void createCourse(const Semester &semester) {
    Course course;
    inputCourse(course, semester);
    saveCourse(course);
}

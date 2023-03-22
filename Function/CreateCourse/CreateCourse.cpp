#include "CreateCourse.h"

#include "../../Struct/LinkedList.h"
#include "../CreateSemester/CreateSemester.h"
#include "../Input/Input.h"
#include "../Normalization/Normalization.h"
#include "../OpenFile/OpenFile.h"

void getAllClassName(Node<std::string> *&allClassName) {
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
    if (cur) {
        cur->next = nullptr;
    }
    fin.close();
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

bool checkValidName(const std::string &name) {
    for (int i = 0; i < name.size(); ++i) {
        if (name[i] == ' ') {
            continue;
        }
        if (name[i] < 'A' || name[i] > 'Z' && name[i] < 'a' || name[i] > 'z') {
            return false;
        }
    }
    return true;
}

bool checkValidDayOfWeek(const std::string &day) {
    return day == "MON" || day == "TUE" || day == "WED" || day == "THU" || day == "FRI" || day == "SAT";
}

void getAllCourse(Node<Course> *&allCourse) {
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

        if (allCourse == nullptr) {
            allCourse = newCourse;
            cur = allCourse;
        } else {
            cur->next = newCourse;
            cur = cur->next;
        }
    }
    fin.close();
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

bool checkCourseNameExist(Node<Course> *allCourse, const std::string &courseName, const std::string &schoolYear) {
    while (allCourse) {
        if (allCourse->data.schoolYearName == schoolYear && allCourse->data.name == courseName) {
            return true;
        }
        allCourse = allCourse->next;
    }
    return false;
}

void inputCourse(
    Course &course, Node<std::string> *&allClassName, const Semester &semester
) {
    getAllClassName(allClassName);
    Node<Course> *allCourse;
    getAllCourse(allCourse);

    bool classNameExist, courseIDExist, courseNameExist, validTeacherName = false, validMaxStudentNumber = false,
                                                         validDayOfWeek = false, validSessionNumber = false, validCredits = false;
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
        std::cout << "Please enter teacher name: ";
        getline(std::cin, course.teacherName);
        normalization(course.teacherName);
        validTeacherName = checkValidName(course.teacherName);
        if (!validTeacherName) {
            std::cout << "Your input is invalid. Please try again!\n";
        }
    } while (!validTeacherName);

    do {
        try {
            std::cout << "Please enter number of credits: ";
            course.credits = intInput();
            validCredits = course.credits > 0 && course.credits <= INT_MAX;
            if (!validCredits) {
                std::cout << "Your input is invaild. Please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what() << '\n';
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
            std::cout << error.what() << '\n';
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
            std::cout << error.what() << '\n';
        }
    } while (!validSessionNumber);

    course.semesterNumber = semester.number;
    course.schoolYearName = semester.schoolYearName;

    deleteLinkedList(allClassName);
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
    Node<std::string> *allClassName = nullptr;
    inputCourse(course, allClassName, semester);
    saveCourse(course);
}

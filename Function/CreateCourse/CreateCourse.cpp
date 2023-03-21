#include "CreateCourse.h"

#include "../../Struct/LinkedList.h"
#include "../Input/Input.h"
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
    return day == "MON" || day == "TUE" || day == "WED" || day == "THU" || day == "FRI" ||
           day == "SAT";
}

void inputCourse(Course &course, Node<std::string> *&allClassName) {
    getAllClassName(allClassName);

    bool classNameExist = false, validTeacherName = false, validOfNumberStudent = false,
         validDayOfWeek = false, validSessionNumber = false;

    std::cout << "Please enter course id: ";
    getline(std::cin, course.id);
    std::cout << "Please enter course name: ";
    getline(std::cin, course.name);

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
        validTeacherName = checkValidName(course.teacherName);
        if (!validTeacherName) {
            std::cout << "Your input is invalid. Please try again!\n";
        }
    } while (!validTeacherName);

    try {
        std::cout << "Please enter number of credits: ";
        course.credits = intInput();
    } catch (std::exception &error) {
        std::cout << error.what() << '\n';
    }

    do {
        try {
            std::cout << "Please enter the maximum number of students in the course: ";
            course.maxStudent = intInput();
            validOfNumberStudent = course.maxStudent >= 1 && course.maxStudent <= 50;
            if (!validOfNumberStudent) {
                std::cout << "Your input is invalid. Please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what() << '\n';
        }
    } while (!validOfNumberStudent);

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

    deleteLinkedList(allClassName);
}

void saveCourse(Course course) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt");
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

void createCourse() {
    Course course;
    Node<std::string> *allClassName = nullptr;
    inputCourse(course, allClassName);
    saveCourse(course);
}

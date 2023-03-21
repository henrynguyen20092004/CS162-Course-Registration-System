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

bool checkClassExist(
    Node<std::string> *allClassName, const std::string &className
) {
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

void inputCourse(Course &allCourse) {
    Node<std::string> *allClassName;
    getAllClassName(allClassName);
    int inputDayOfWeek, inputSessionNumber;
    bool checkClassNameExist = false, checkValidTeacherName = false,
         checkMaximumStudent = false, validDayOfWeek = false,
         validSessionNumber = false;
    std::cout << "Please enter course id: ";
    getline(std::cin, allCourse.id);
    std::cout << "Please enter course name: ";
    getline(std::cin, allCourse.name);

    do {
        std::cout << "Please enter class name: ";
        getline(std::cin, allCourse.className);
        checkClassNameExist =
            checkClassExist(allClassName, allCourse.className);
        if (!checkClassNameExist) {
            std::cout << "This class does not exist. Please enter again!\n";
        }
    } while (!checkClassNameExist);

    do {
        std::cout << "Please enter teacher name: ";
        getline(std::cin, allCourse.teacherName);
        checkValidTeacherName = checkValidName(allCourse.teacherName);
        if (!checkValidTeacherName) {
            std::cout << "Your input is invalid. Please enter again!\n";
        }
    } while (!checkValidTeacherName);

    std::cout << "Please enter number of credits: ";
    allCourse.credits = intInput();

    do {
        std::cout
            << "Please enter the maximum number of students in the course: ";
        allCourse.maxStudent = intInput();
        checkMaximumStudent =
            allCourse.maxStudent >= 1 && allCourse.maxStudent <= 50;
        if (!checkMaximumStudent) {
            std::cout << "Your input is invalid. Please enter again!\n";
        }
    } while (!checkMaximumStudent);

    do {
        try {
            std::cout << "Please choose day of week that the course will be "
                         "perfomed: ";
            inputDayOfWeek = intInput();
            validDayOfWeek = inputDayOfWeek > 0 && inputDayOfWeek <= 6;
            if (validDayOfWeek) {
                allCourse.dayOfWeek = static_cast<DayOfWeek>(inputDayOfWeek);
            } else {
                std::cout << "Invalid day of week, please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what() << '\n';
        }
    } while (!validDayOfWeek);

    do {
        try {
            std::cout << "Please choose day of week that the course will be "
                         "perfomed: ";
            inputSessionNumber = intInput();
            validSessionNumber =
                inputSessionNumber > 0 && inputSessionNumber <= 4;
            if (validSessionNumber) {
                allCourse.sessionNumber =
                    static_cast<SessionNumber>(inputSessionNumber);
            } else {
                std::cout << "Invalid session number, please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what() << '\n';
        }
    } while (!validSessionNumber);
    deleteLinkedList(allClassName);
}
void saveCourse(Course allCourse) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt");
    fout << allCourse.id << '\n';
    fout << allCourse.name << '\n';
    fout << allCourse.className << '\n';
    fout << allCourse.teacherName << '\n';
    fout << allCourse.credits << '\n';
    fout << allCourse.maxStudent << '\n';
    fout << allCourse.dayOfWeek << '\n';
    fout << allCourse.sessionNumber << '\n';
    fout.close();
}
void createCourse() {
    Course allCourse;
    inputCourse(allCourse);
    saveCourse(allCourse);
}
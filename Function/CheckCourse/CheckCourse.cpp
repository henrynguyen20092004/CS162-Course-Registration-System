#include "CheckCourse.h"

#include "../OpenFile/OpenFile.h"

Node<std::string> *getAllClassName() {
    std::ifstream fin;
    readFile(fin, "Data/Class.txt");
    Node<std::string> *cur = nullptr, *allClassName = nullptr;
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

bool checkCourseExist(
    Node<Course> *allCourse, const std::string &courseID, const std::string &className
) {
    while (allCourse) {
        if (allCourse->data.className == className && allCourse->data.id == courseID) {
            return true;
        }
        allCourse = allCourse->next;
    }
    return false;
}

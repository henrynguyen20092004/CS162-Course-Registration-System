#include "GetAllCoursesOfStudentsInClass.h"

#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../Check/CheckStudentID/CheckStudentID.h"
#include "../../GetAll/GetAllStudents/GetAllStudents.h"
#include "../../GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"

bool isExistedInList(Node<std::string>*& allItems, std::string item) {
    Node<std::string>* cur = allItems;
    while (cur) {
        if (cur->data == item) {
            return true;
        }
        cur = cur->next;
    }
    deleteLinkedList(cur);
    return false;
}

Node<std::string>* getAllCoursesOfStudentsInClass(Node<Score>* allScoresOfClass) {
    Node<Score>* cur = allScoresOfClass;
    Node<std::string>* allCoursesOfStudentsInClass = nullptr;

    while (cur) {
        std::string fullCourseName =
            cur->data.studentCourse.courseID + "-" + cur->data.studentCourse.className;
        if (!isExistedInList(allCoursesOfStudentsInClass, fullCourseName)) {
            Node<std::string>* new_node = new Node<std::string>(fullCourseName);
            addNewItemsToOldList(allCoursesOfStudentsInClass, new_node);
        }
        cur = cur->next;
    }

    deleteLinkedList(cur);
    return allCoursesOfStudentsInClass;
}

int getCourseCredits(
    Node<Course>* allCourses, const std::string& courseID, const std::string& className
) {
    for (Node<Course>* cur = allCourses; cur; cur = cur->next) {
        if (cur->data.id == courseID && cur->data.className == className) {
            return cur->data.credits;
        }
    }
}

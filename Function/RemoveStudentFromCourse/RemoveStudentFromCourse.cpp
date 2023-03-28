#include "RemoveStudentFromCourse.h"

#include "../../Struct/Student_Course.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../SaveCourse/SaveCourse.h"

void inputStudent_Course(Student_Course &studentCourse) {
    std::cout << "Please enter the student's id: ";
    getline(std::cin, studentCourse.studentID);
    std::cout << "Please enter the id of the student's course: ";
    getline(std::cin, studentCourse.courseID);
    std::cout << "Please enter the class name of this course: ";
    getline(std::cin, studentCourse.className);
}

void removeStudent(const Student_Course &studentCourse, bool &studentExist) {
    Node<Student_Course> *allStudentInCourse = getAllStudent_Courses();
    Node<Student_Course> *cur = allStudentInCourse, *prev = nullptr;

    while (cur) {
        if (cur->data.courseID == studentCourse.courseID &&
            cur->data.studentID == studentCourse.studentID &&
            cur->data.className == studentCourse.className) {
            Node<Student_Course> *tmpStudentCourse = cur;

            if (!prev) {
                allStudentInCourse = cur->next;
            } else {
                prev->next = cur->next;
            }
            std::cout << "Removing student successfully!\n";
            studentExist = true;
            delete tmpStudentCourse;
            break;
        }
        prev = cur;
        cur = cur->next;
    }

    saveAllStudent_Course(allStudentInCourse);
    deleteLinkedList(allStudentInCourse);
}

void removeAStudentInCourse() {
    Student_Course studentCourse;
    bool studentExist = false;

    do {
        inputStudent_Course(studentCourse);
        removeStudent(studentCourse, studentExist);
        if (!studentExist) {
            std::cout << "Removing student failed, please try again!\n";
        }
    } while (!studentExist);
}

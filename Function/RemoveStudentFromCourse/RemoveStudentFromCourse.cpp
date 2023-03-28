#include "RemoveStudentFromCourse.h"

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
    Node<Student_Course> *allStudentInCourse =
                             new Node<Student_Course>(getAllStudent_Courses()),
                         *cur = allStudentInCourse;

    while (cur->next) {
        if (cur->next->data.courseID == studentCourse.courseID &&
            cur->next->data.studentID == studentCourse.studentID &&
            cur->next->data.className == studentCourse.className) {
            Node<Student_Course> *tmpStudentCourse = cur->next;
            cur->next = cur->next->next;
            studentExist = true;
            delete tmpStudentCourse;
            break;
        }
        cur = cur->next;
    }

    saveAllStudent_Course(allStudentInCourse->next);
    deleteLinkedList(allStudentInCourse);
}

void removeStudentFromCourse() {
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

#include "RemoveStudentFromCourse.h"

#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"
#include "../SaveCourse/SaveCourse.h"

void removeStudent(
    Node<StudentCourse> *allStudentCourses, const StudentCourse &studentCourse
) {
    Node<StudentCourse> *cur = allStudentCourses, *tmpStudentCourse;

    for (; cur->next; cur = cur->next) {
        tmpStudentCourse = cur->next;

        if (tmpStudentCourse->data.courseID == studentCourse.courseID &&
            tmpStudentCourse->data.studentID == studentCourse.studentID &&
            tmpStudentCourse->data.className == studentCourse.className) {
            cur->next = tmpStudentCourse->next;
            delete tmpStudentCourse;
            saveAllStudentCourses(allStudentCourses->next);
            return;
        }
    }
}

void removeStudentFromCourse() {
    Node<StudentCourse> *allStudentCourses = new Node(getAllStudentCourses());

    if (!allStudentCourses) {
        std::cout << "There's no student enrolling in a course right now!\n";
        return;
    }

    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    StudentCourse studentCourse;
    bool studentExist = false;

    do {
        try {
            inputStudentCourse(studentCourse);
            validateStudentCourse(allStudents, allClasses, allCourses, studentCourse);

            if (!checkStudentInCourse(
                    allStudentCourses, studentCourse.studentID, studentCourse.courseID,
                    studentCourse.className
                )) {
                std::cout << "This student isn't in the course, please try again!\n";
                continue;
            }

            removeStudent(allStudentCourses, studentCourse);
            studentExist = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!studentExist);

    deleteLinkedList(allStudentCourses);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
    std::cout << "Student successfully removed!\n";
}

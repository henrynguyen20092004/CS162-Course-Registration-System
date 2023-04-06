#include "RemoveStudentFromCourse.h"

#include "../../Struct/Data.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../InputAndValidate/InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"
#include "../Save/SaveCourse/SaveCourse.h"

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
    if (!allData.allStudentCourses) {
        std::cout << "There's no student enrolling in a course right now!\n";
        return;
    }

    Node<StudentCourse> *allStudentCourses = new Node(allData.allStudentCourses);
    StudentCourse studentCourse;
    bool studentExist = false;

    do {
        try {
            inputStudentCourse(studentCourse);
            validateStudentCourse(
                allData.allStudents, allData.allClasses, allData.allCourses, studentCourse
            );

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

    allData.allStudentCourses = allStudentCourses->next;
    delete allStudentCourses;
    std::cout << "Student successfully removed!\n";
}

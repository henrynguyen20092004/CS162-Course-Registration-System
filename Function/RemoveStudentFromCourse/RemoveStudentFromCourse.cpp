#include "RemoveStudentFromCourse.h"

#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputStudentCourse/InputStudentCourse.h"
#include "../SaveCourse/SaveCourse.h"
#include "../ValidateStudentCourse/ValidateStudentCourse.h"

void removeStudent(
    Node<Student_Course> *allStudent_Courses, const Student_Course &student_course
) {
    Node<Student_Course> *cur = allStudent_Courses, *tmpStudentCourse;

    for (; cur->next; cur = cur->next) {
        tmpStudentCourse = cur->next;

        if (tmpStudentCourse->data.courseID == student_course.courseID &&
            tmpStudentCourse->data.studentID == student_course.studentID &&
            tmpStudentCourse->data.className == student_course.className) {
            cur->next = tmpStudentCourse->next;
            delete tmpStudentCourse;
            saveAllStudent_Course(allStudent_Courses->next);
            return;
        }
    }
}

void removeStudentFromCourse() {
    Node<Student_Course> *allStudent_Courses = new Node(getAllStudent_Courses());
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    Student_Course student_course;
    bool studentExist = false;

    do {
        try {
            inputStudent_Course(student_course);
            validateStudent_Course(allStudents, allClasses, allCourses, student_course);

            if (!checkStudentInCourse(
                    allStudent_Courses, student_course.studentID, student_course.courseID,
                    student_course.className
                )) {
                std::cout << "This student isn't in the course, please try again!\n";
                continue;
            }

            removeStudent(allStudent_Courses, student_course);
            studentExist = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!studentExist);

    deleteLinkedList(allStudent_Courses);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
}

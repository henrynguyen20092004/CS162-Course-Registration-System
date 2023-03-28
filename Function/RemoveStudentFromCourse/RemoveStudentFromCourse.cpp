#include "RemoveStudentFromCourse.h"

#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../InputStudentCourse/InputStudentCourse.h"
#include "../SaveCourse/SaveCourse.h"
#include "../ValidateStudentCourse/ValidateStudentCourse.h"

void removeStudent(
    Node<Student_Course> *allStudent_Courses, const Student_Course &studentCourse
) {
    Node<Student_Course> *cur = allStudent_Courses;

    while (cur->next) {
        if (cur->next->data.courseID == studentCourse.courseID &&
            cur->next->data.studentID == studentCourse.studentID &&
            cur->next->data.className == studentCourse.className) {
            Node<Student_Course> *tmpStudentCourse = cur->next;
            cur->next = cur->next->next;
            delete tmpStudentCourse;
            saveAllStudent_Course(allStudent_Courses->next);
            return;
        }

        cur = cur->next;
    }

    throw std::invalid_argument("This student is not in the course, please try again!\n");
}

void removeStudentFromCourse() {
    Node<Student_Course> *allStudent_Courses = new Node(getAllStudent_Courses());
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Node<Course> *allCourses = getAllCourses();
    Student_Course studentCourse;
    bool studentExist = false;

    do {
        try {
            inputStudent_Course(studentCourse);
            validateStudent_Course(allStudents, allClasses, allCourses, studentCourse);
            removeStudent(allStudent_Courses, studentCourse);
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

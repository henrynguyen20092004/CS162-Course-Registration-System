#include "ValidateStudentCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"

void validateStudent_Course(
    Node<Student> *allStudents, Node<std::string> *allClasses, Node<Course> *allCourses,
    const Student_Course &student_course
) {
    if (!checkStudentIDExists(allStudents, student_course.studentID)) {
        throw std::invalid_argument("This student does not exist, please try again!\n");
    }

    if (!checkClassExists(allClasses, student_course.className)) {
        throw std::invalid_argument("This class does not exist, please try again!\n");
    }

    if (!checkCourseExists(
            allCourses, student_course.courseID, student_course.className
        )) {
        throw std::invalid_argument("This course does not exist, please try again!\n");
    }
}

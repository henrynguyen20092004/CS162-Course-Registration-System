#include "ValidateStudentCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"

void validateStudent_Course(
    Node<Student> *allStudents, Node<std::string> *allClasses, Node<Course> *allCourses,
    const Student_Course &studentCourse
) {
    if (!checkStudentIDExists(allStudents, studentCourse.studentID)) {
        throw std::invalid_argument("This student does not exist, please try again!\n");
    }

    if (!checkClassExists(allClasses, studentCourse.className)) {
        throw std::invalid_argument("This class does not exist, please try again!\n");
    }

    if (!checkCourseExists(allCourses, studentCourse.courseID, studentCourse.className)) {
        throw std::invalid_argument("This course does not exist, please try again!\n");
    }
}

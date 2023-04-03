#ifndef INPUT_AND_VALIDATE_STUDENT_COURSE_H
#define INPUT_AND_VALIDATE_STUDENT_COURSE_H

#include "../../../Struct/Course.h"
#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Student.h"
#include "../../../Struct/StudentCourse.h"

void inputStudentCourse(StudentCourse &studentCourse);
void validateStudentCourse(
    Node<Student> *allStudents, Node<std::string> *allClasses, Node<Course> *allCourses,
    const StudentCourse &studentCourse
);

#endif

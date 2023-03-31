#ifndef INPUT_AND_VALIDATE_STUDENT_COURSE_H
#define INPUT_AND_VALIDATE_STUDENT_COURSE_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"
#include "../../Struct/Student_Course.h"

void inputStudentCourse(Student_Course &student_course);
void validateStudent_Course(
    Node<Student> *allStudents, Node<std::string> *allClasses, Node<Course> *allCourses,
    const Student_Course &student_course
);

#endif

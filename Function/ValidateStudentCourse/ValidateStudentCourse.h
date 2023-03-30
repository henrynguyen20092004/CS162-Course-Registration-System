#ifndef VALIDATE_STUDENT_COURSE
#define VALIDATE_STUDENT_COURSE

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"
#include "../../Struct/Student_Course.h"

void validateStudent_Course(
    Node<Student> *allStudents, Node<std::string> *allClasses, Node<Course> *allCourses,
    const Student_Course &student_course
);

#endif

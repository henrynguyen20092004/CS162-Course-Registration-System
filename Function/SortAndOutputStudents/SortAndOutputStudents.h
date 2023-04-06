#ifndef SORT_AND_OUTPUT_STUDENT_H
#define SORT_AND_OUTPUT_STUDENT_H

#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"

void sortAndOutputStudents(
    std::ostream& out, Node<Student>* allStudents,
    void (*outputStudentsCallBack
    )(std::ostream& out, Student* allStudentsArray, int arraySize)
);

#endif

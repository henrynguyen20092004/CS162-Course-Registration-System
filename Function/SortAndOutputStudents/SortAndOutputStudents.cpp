#include "SortAndOutputStudents.h"

#include <algorithm>

bool compareStudent(const Student& firstStudent, const Student& secondStudent) {
    return firstStudent.id < secondStudent.id;
}

void sortAndOutputStudents(
    std::ostream& out, Node<Student>* allStudents,
    void (*outputStudentsCallBack
    )(std::ostream& out, Student* allStudentsArray, int arraySize)
) {
    int arraySize;
    Student* allStudentsArray;
    transformLinkedListToArray(allStudents, allStudentsArray, arraySize);
    std::sort(allStudentsArray, allStudentsArray + arraySize, compareStudent);
    outputStudentsCallBack(out, allStudentsArray, arraySize);
    delete[] allStudentsArray;
    deleteLinkedList(allStudents);
}

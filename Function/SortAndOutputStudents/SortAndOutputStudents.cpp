#include "SortAndOutputStudents.h"

#include <algorithm>

int getLinkedListSize(Node<Student>* head) {
    int result = 0;
    for (; head; head = head->next) {
        ++result;
    }
    return result;
}

bool compareStudent(const Student& firstStudent, const Student& secondStudent) {
    return firstStudent.id < secondStudent.id;
}

void sortAndOutputStudents(
    std::ostream& out, Node<Student>* allStudents,
    void (*outputStudentsFunction
    )(std::ostream& out, Student* allStudentsArray, int arraySize)
) {
    int arraySize = getLinkedListSize(allStudents);
    Student* allStudentsArray = new Student[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        allStudentsArray[i] = allStudents->data;
        allStudents = allStudents->next;
    }

    std::sort(allStudentsArray, allStudentsArray + arraySize, compareStudent);
    outputStudentsFunction(out, allStudentsArray, arraySize);
    delete[] allStudentsArray;
    deleteLinkedList(allStudents);
}

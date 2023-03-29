#include "SortAndDisplayStudent.h"

#include <algorithm>

#include "../DisplayStudentInfo/DisplayStudentInfo.h"

int getLinkedListSize(Node<Student>* head) {
    int result = 0;
    for (; head; head = head->next) {
        result++;
    }
    return result;
}

bool compareStudent(const Student& firstStudent, const Student& secondStudent) {
    return firstStudent.id < secondStudent.id;
}

void sortAndDisplayStudent(Node<Student>* allStudents) {
    int sizeOfArray = getLinkedListSize(allStudents);
    Student* allStudentsArray = new Student[sizeOfArray];

    for (int i = 0; i < sizeOfArray; ++i) {
        allStudentsArray[i] = allStudents->data;
        allStudents = allStudents->next;
    }

    std::sort(allStudentsArray, allStudentsArray + sizeOfArray, compareStudent);

    for (int i = 0; i < sizeOfArray; ++i) {
        std::cout << "\nThis is the student number " << i + 1 << ":\n";
        displayStudentInfo(allStudentsArray[i]);
    }

    delete[] allStudentsArray;
    deleteLinkedList(allStudents);
}

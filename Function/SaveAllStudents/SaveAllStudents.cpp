#include "SaveAllStudents.h"

#include "../OpenFile/OpenFile.h"

void saveAllStudents(Node<Student>* allStudents) {
    std::ofstream fout;
    writeFile(fout, "Data/Student.txt");
    for (; allStudents; allStudents = allStudents->next) {
        Student tmpStudent = allStudents->data;
        fout << tmpStudent.id << '\n';
        fout << tmpStudent.firstName << '\n';
        fout << tmpStudent.lastName << '\n';
        fout << tmpStudent.gender << '\n';
        fout << tmpStudent.dateOfBirth << '\n';
        fout << tmpStudent.socialID << '\n';
        fout << tmpStudent.className << '\n';
    }
    fout.close();
}
#include "SaveStudent.h"

#include "../../OpenFile/OpenFile.h"

void saveAllStudents(Node<Student>* allStudents) {
    std::ofstream fout;
    writeFile(fout, "Data/Student.txt");

    for (; allStudents; allStudents = allStudents->next) {
        Student student = allStudents->data;
        fout << student.id << '\n';
        fout << student.firstName << '\n';
        fout << student.lastName << '\n';
        fout << student.gender << '\n';
        fout << student.dateOfBirth << '\n';
        fout << student.socialID << '\n';
        fout << student.className << '\n';
    }

    fout.close();
}

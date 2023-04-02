#include "CreateStudent.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../CreateStudentAccount/CreateStudentAccount.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../InputAndValidateStudent/InputAndValidateStudent.h"

void saveCreatedStudent(const Student &student) {
    std::ofstream fout;
    writeFile(fout, "Data/Student.txt", std::ios::app);
    fout << student.id << '\n';
    fout << student.firstName << '\n';
    fout << student.lastName << '\n';
    fout << student.gender << '\n';
    fout << student.dateOfBirth << '\n';
    fout << student.socialID << '\n';
    fout << student.className << '\n';
    fout.close();
}

void createStudent() {
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Student student;
    bool validStudent = false;

    do {
        try {
            inputStudent(student);

            if (checkStudentIDExists(allStudents, student.id)) {
                std::cout << "This student already exists, please try again!\n";
                continue;
            }

            validateStudent(allClasses, student);
            validStudent = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudent);

    saveCreatedStudent(student);
    createStudentAccount(student);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    std::cout << "Student successfully added!\n";
}

#include "CreateStudent.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckStudentID/CheckStudentID.h"
#include "../../DateFunction/DateFunction.h"
#include "../../Input/Input.h"
#include "../../InputAndValidate/InputAndValidateStudent/InputAndValidateStudent.h"
#include "../CreateStudentAccount/CreateStudentAccount.h"

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
    addNewItemsToOldList(allData.allStudents, new Node(student));
}

void createStudent() {
    Student student;
    bool validStudent = false;

    do {
        try {
            inputStudent(student);

            if (checkStudentIDExists(allData.allStudents, student.id)) {
                std::cout << "This student already exists, please try again!\n";
                continue;
            }

            validateStudent(allData.allClasses, student);
            validStudent = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudent);

    saveCreatedStudent(student);
    createStudentAccount(student);
    std::cout << "Student successfully added!\n";
}

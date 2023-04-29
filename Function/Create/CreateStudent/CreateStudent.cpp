#include "CreateStudent.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckStudent/CheckStudent.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../InputAndValidate/InputAndValidateStudent/InputAndValidateStudent.h"
#include "../CreateStudentAccount/CreateStudentAccount.h"

void saveStudent(const Student &student) {
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

void createStudent(char **inputs, char **dropDownItems) {
    Student student;
    student.id = inputs[0];
    student.className = dropDownItems[0];
    student.firstName = checkAndConvertToName(inputs[1], "first name");
    student.lastName = checkAndConvertToName(inputs[2], "last name");
    student.gender = dropDownItems[1];
    student.dateOfBirth = inputs[3];
    student.socialID = inputs[4];

    if (checkStudentIDExists(allData.allStudents, student.id)) {
        throw std::invalid_argument("This student already exists, please try again!");
    }

    validateStudent(allData.allClasses, student);
    saveStudent(student);
    createStudentAccount(student);
}

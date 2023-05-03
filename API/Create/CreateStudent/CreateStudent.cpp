#include "CreateStudent.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckStudent/CheckStudent.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../DateFunction/DateFunction.h"
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
    addNewItemsToOldList(GlobalVar::allData.allStudents, new Node(student));
}

void createStudent(char **inputs, char **dropDownItems, const std::string &className) {
    Student student;
    student.id = inputs[0];
    student.className = className;
    student.firstName = checkAndConvertToName(inputs[1], "first name");
    student.lastName = checkAndConvertToName(inputs[2], "last name");
    student.gender = dropDownItems[0];
    student.dateOfBirth = inputs[3];
    student.socialID = inputs[4];

    if (checkStudentIDExists(GlobalVar::allData.allStudents, student.id)) {
        throw std::invalid_argument("Student ID already exists, please try again!");
    }

    if (!checkDate(student.dateOfBirth) ||
        !compareDate(student.dateOfBirth, getToday())) {
        throw std::invalid_argument("Invalid date of birth, please try again!");
    }

    saveStudent(student);
    createStudentAccount(student);
}

#include "CreateStudent.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckStudentID/CheckStudentID.h"
#include "../../DateFunction/DateFunction.h"
// #include "../../Input/Input.h"
#include "../../InputAndValidate/InputAndValidateStudent/InputAndValidateStudent.h"
#include "../CreateStudentAccount/CreateStudentAccount.h"

void saveCreatedStudent(const Student& student) {
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

void createStudent(
    char* studentID, char* firstName, char* lastName, char* gender, char* dateOfBirth,
    char* socialID, char* className
) {
    Student student;
    student.id = studentID;
    if (checkStudentIDExists(allData.allStudents, student.id)) {
        throw std::invalid_argument("This student already exists, please try again!");
    }

    student.firstName = firstName;
    student.lastName = lastName;
    student.gender = gender;
    student.dateOfBirth = dateOfBirth;
    student.socialID = socialID;
    student.className = className;

    validateStudent(allData.allClasses, student);
    saveCreatedStudent(student);
    createStudentAccount(student);
    std::cout << "Student successfully added!";
}

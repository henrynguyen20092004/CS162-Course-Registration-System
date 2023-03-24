#include "CreateStudent.h"

#include "../../Struct/Student.h"
#include "../CheckDate/CheckDate.h"
#include "../CheckStudentID/CheckStudentID.h"
#include "../CreateStudentAccount/CreateStudentAccount.h"
#include "../GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

Student inputStudent(const std::string &className) {
    Student student;
    bool validGender;
    bool validDate;
    std::cout << "Please fill information required in every box\n";
    std::cout
        << "If any requirement is repeated, it means your entrance data is illegal\n";
    do {
        std::cout << "Student ID: ";
        getline(std::cin, student.id);
    } while (checkStudentID(student.id));
    std::cout << "First name (only one word): ";
    student.firstName = nameInput();
    std::cout << "Last name: ";
    student.lastName = nameInput();

    do {
        std::cout << "Gender (M: Male, F: Female): ";
        std::string gender;
        getline(std::cin, gender);

        if (gender == "M" || gender == "m") {
            student.gender = "M";
            validGender = true;
        } else if (gender == "F" || gender == "f") {
            student.gender = "F";
            validGender = true;
        } else {
            validGender = false;
        }
    } while (!validGender);

    do {
        std::cout << "Enter the date of birth: ";
        getline(std::cin, student.dateOfBirth);
        validDate = checkDate(student.dateOfBirth);
    } while (!validDate);

    std::cout << "Enter the social ID: ";
    getline(std::cin, student.socialID);
    student.className = className;
    return student;
}

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
    fout << '\n';
    fout.close();
    std::cout << "Add one student successfully!\n";
}

void createStudent(const std::string &className) {
    Student student = inputStudent(className);
    saveStudent(student);
    createStudentAccount(student);
}

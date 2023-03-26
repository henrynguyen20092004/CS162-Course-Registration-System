#include "CreateStudent.h"

#include "../CheckClass/CheckClass.h"
#include "../CheckDate/CheckDate.h"
#include "../CheckStudentID/CheckStudentID.h"
#include "../CreateStudentAccount/CreateStudentAccount.h"
#include "../GetAllClasses/GetAllClasses.h"
#include "../GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

Student inputStudent() {
    Student student;
    bool studentExists, classExists, validFirstName, validLastName, validGender,
        validDate;
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    std::cout << "Please fill the information in every box\n";

    do {
        std::cout << "Student ID: ";
        getline(std::cin, student.id);
        studentExists = checkStudentIDExists(allStudents, student.id);

        if (studentExists) {
            std::cout << "This student already exists, please try again!\n";
        }
    } while (studentExists);

    do {
        try {
            std::cout << "First name (only one word): ";
            student.firstName = nameInput();
            validFirstName = true;
        } catch (std::exception &error) {
            std::cout << error.what();
            validFirstName = false;
        }
    } while (!validFirstName);

    do {
        try {
            std::cout << "Last name: ";
            student.lastName = nameInput();
            validLastName = true;
        } catch (std::exception &error) {
            std::cout << error.what();
            validLastName = false;
        }
    } while (!validLastName);

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
            std::cout << "Invalid gender, please enter F or M!\n";
            validGender = false;
        }
    } while (!validGender);

    do {
        std::cout << "Date of birth (dd/mm/yyyy): ";
        getline(std::cin, student.dateOfBirth);
        validDate = checkDate(student.dateOfBirth);

        if (!validDate) {
            std::cout << "Invalid date of birth, please try again! \n";
        }
    } while (!validDate);

    std::cout << "Social ID: ";
    getline(std::cin, student.socialID);

    do {
        std::cout << "Class name: ";
        getline(std::cin, student.className);
        classExists = checkClassExists(allClasses, student.className);

        if (!classExists) {
            std::cout << "This class doesn't exists, please try again!\n";
        }
    } while (!classExists);

    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
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
    fout.close();
    std::cout << "Student successfully added!\n";
}

void createStudent() {
    Student student = inputStudent();
    saveStudent(student);
    createStudentAccount(student);
}

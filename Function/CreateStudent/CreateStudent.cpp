#include "CreateStudent.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../CreateStudentAccount/CreateStudentAccount.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"

void validateStudent(
    Node<Student> *allStudents, Node<std::string> *allClasses, Student &student
) {
    if (checkStudentIDExists(allStudents, student.id)) {
        throw std::invalid_argument("This student already exists, please try again!\n");
    }

    if (student.gender == "M" || student.gender == "m") {
        student.gender = "M";
    } else if (student.gender == "F" || student.gender == "f") {
        student.gender = "F";
    } else {
        throw std::invalid_argument("Invalid gender, please try again!\n");
    }

    if (!checkDate(student.dateOfBirth)) {
        throw std::invalid_argument("Invalid date of birth, please try again!\n");
    }

    if (!checkClassExists(allClasses, student.className)) {
        throw std::invalid_argument(
            "This class doesn't exists, please create it or try again!\n"
        );
    }
}

void inputStudent(Student &student) {
    std::cout << "Please fill the information in every box\n";
    std::cout << "Student ID: ";
    getline(std::cin, student.id);
    std::cout << "First name (only one word): ";
    student.firstName = nameInput();
    std::cout << "Last name: ";
    student.lastName = nameInput();
    std::cout << "Gender (M: Male, F: Female): ";
    getline(std::cin, student.gender);
    std::cout << "Date of birth (dd/mm/yyyy): ";
    getline(std::cin, student.dateOfBirth);
    std::cout << "Social ID: ";
    getline(std::cin, student.socialID);
    std::cout << "Class name: ";
    getline(std::cin, student.className);
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
}

void createStudent() {
    Node<Student> *allStudents = getAllStudents();
    Node<std::string> *allClasses = getAllClasses();
    Student student;
    bool validStudent = false;

    do {
        try {
            inputStudent(student);
            validateStudent(allStudents, allClasses, student);
            validStudent = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudent);

    saveStudent(student);
    createStudentAccount(student);
    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    std::cout << "Student successfully added!\n";
}

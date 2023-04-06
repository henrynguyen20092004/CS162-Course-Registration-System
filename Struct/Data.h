#ifndef DATA_H
#define DATA_H

#include "../Function/GetAll/GetAllClasses/GetAllClasses.h"
#include "../Function/GetAll/GetAllCourses/GetAllCourses.h"
#include "../Function/GetAll/GetAllSchoolYears/GetAllSchoolYears.h"
#include "../Function/GetAll/GetAllScores/GetAllScores.h"
#include "../Function/GetAll/GetAllSemesters/GetAllSemesters.h"
#include "../Function/GetAll/GetAllStudents/GetAllStudents.h"
#include "../Function/GetAll/GetAllUsers/GetAllUsers.h"

struct Data {
    Node<std::string> *allSchoolYears = getAllSchoolYears();
    Node<Semester> *allSemesters = getAllSemesters();
    Node<Course> *allCourses = getAllCourses();
    Node<std::string> *allClasses = getAllClasses();
    Node<Score> *allScores = getAllScores();
    Node<User> *allUsers = getAllUsers();
    Node<Student> *allStudents = getAllStudents();
    Node<StudentCourse> *allStudentCourses = getAllStudentCourses();

    ~Data() {
        deleteLinkedList(allSchoolYears);
        deleteLinkedList(allSemesters);
        deleteLinkedList(allCourses);
        deleteLinkedList(allClasses);
        deleteLinkedList(allScores);
        deleteLinkedList(allUsers);
        deleteLinkedList(allStudents);
        deleteLinkedList(allStudentCourses);
    }
};

extern Data allData;

#endif

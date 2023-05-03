#ifndef DATA_H
#define DATA_H

#include "../API/GetAll/GetAllClasses/GetAllClasses.h"
#include "../API/GetAll/GetAllCourses/GetAllCourses.h"
#include "../API/GetAll/GetAllSchoolYears/GetAllSchoolYears.h"
#include "../API/GetAll/GetAllScores/GetAllScores.h"
#include "../API/GetAll/GetAllSemesters/GetAllSemesters.h"
#include "../API/GetAll/GetAllStudents/GetAllStudents.h"
#include "../API/GetAll/GetAllUsers/GetAllUsers.h"

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

#endif

#include "GetAllStudents.h"

void readStudent(std::ifstream &fin, Student &student) {
    getline(fin, student.id);
    getline(fin, student.firstName);
    getline(fin, student.lastName);
    getline(fin, student.gender);
    getline(fin, student.dateOfBirth);
    getline(fin, student.socialID);
    getline(fin, student.className);
}

Node<Student> *getAllStudents() { return getAll("Data/Student.txt", &readStudent); }

void readStudentCourse(std::ifstream &fin, StudentCourse &studentCourse) {
    std::string course_class;
    getline(fin, studentCourse.studentID);
    getline(fin, studentCourse.courseID);
    getline(fin, studentCourse.className);
}

Node<StudentCourse> *getAllStudentCourses() {
    return getAll("Data/StudentCourse.txt", &readStudentCourse);
}

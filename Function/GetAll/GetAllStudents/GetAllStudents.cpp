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

Node<Student> *getAllStudents() {
    return getAll("Data/Student.txt", &readStudent);
}

void readStudent_Course(std::ifstream &fin, Student_Course &student_course) {
    std::string course_class;
    getline(fin, student_course.studentID);
    getline(fin, course_class);
    student_course.courseID = course_class.substr(0, course_class.find('-'));
    student_course.className = course_class.substr(course_class.find('-') + 1);
}

Node<Student_Course> *getAllStudent_Courses() {
    return getAll("Data/Student_Course.txt", &readStudent_Course);
}

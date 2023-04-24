#include "OperatorOverload.h"

bool operator==(const Student &firstStudent, const Student &secondStudent) {
    return firstStudent.id == secondStudent.id &&
           firstStudent.firstName == secondStudent.firstName &&
           firstStudent.lastName == secondStudent.lastName &&
           firstStudent.gender == secondStudent.gender &&
           firstStudent.dateOfBirth == secondStudent.dateOfBirth &&
           firstStudent.socialID == secondStudent.socialID &&
           firstStudent.className == secondStudent.className;
}

bool operator==(const Score &firstScore, const Score &secondScore) {
    return firstScore.studentCourse == secondScore.studentCourse &&
           firstScore.otherMark == secondScore.otherMark &&
           firstScore.midtermMark == secondScore.midtermMark &&
           firstScore.finalMark == secondScore.finalMark &&
           firstScore.totalMark == secondScore.totalMark;
}

bool operator==(
    const StudentCourse &firstStudentCourse, const StudentCourse &secondStudentCourse
) {
    return firstStudentCourse.studentID == secondStudentCourse.studentID &&
           firstStudentCourse.courseID == secondStudentCourse.courseID &&
           firstStudentCourse.className == secondStudentCourse.className;
}

bool operator<(const Student &firstStudent, const Student &secondStudent) {
    return firstStudent.id.size() == secondStudent.id.size()
               ? firstStudent.id < secondStudent.id
               : firstStudent.id.size() < secondStudent.id.size();
}

bool operator<(const Course &firstCourse, const Course &secondCourse) {
    return firstCourse.name < secondCourse.name;
}
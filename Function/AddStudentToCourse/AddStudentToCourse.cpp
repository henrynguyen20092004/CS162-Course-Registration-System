#include "AddStudentToCourse.h"

#include "../../Struct/Data.h"
#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../InputAndValidate/InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"

void saveStudentToCourse(const StudentCourse &studentCourse) {
    std::ofstream fout;
    writeFile(fout, "Data/StudentCourse.txt", std::ios::app);
    fout << studentCourse.studentID << '\n';
    fout << studentCourse.courseID << '\n';
    fout << studentCourse.className << '\n';
    fout.close();
    addNewItemsToOldList(allData.allStudentCourses, new Node(studentCourse));
}

void addStudentToCourse(char *courseID, char *className, char *studentID) {
    StudentCourse studentCourse;

    studentCourse.courseID = courseID;
    studentCourse.className = className;
    studentCourse.studentID = studentID;

    validateStudentCourse(
        allData.allStudents, allData.allClasses, allData.allCourses, studentCourse
    );

    if (checkStudentInCourse(
            allData.allStudentCourses, studentCourse.studentID, studentCourse.courseID,
            studentCourse.className
        )) {
        throw std::invalid_argument(
            "This student is already in the course, please try again!\n"
        );
    }
    saveStudentToCourse(studentCourse);
}

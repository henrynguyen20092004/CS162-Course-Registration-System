#include "AddStudentToCourse.h"

#include "../../Struct/Data.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../InputAndValidate/InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"
#include "../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void saveStudentToCourse(const StudentCourse &studentCourse) {
    std::ofstream fout;
    writeFile(fout, "Data/StudentCourse.txt", std::ios::app);
    fout << studentCourse.studentID << '\n';
    fout << studentCourse.courseID << '\n';
    fout << studentCourse.className << '\n';
    fout.close();
    addNewItemsToOldList(allData.allStudentCourses, new Node(studentCourse));
}

void addStudentToCourse(char **inputs, char **dropDownItems) {
    StudentCourse studentCourse;
    studentCourse.studentID = inputs[0];

    std::string *courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, dropDownItems[0]);
    studentCourse.courseID = courseIDAndClassName[0];
    studentCourse.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

    if (!checkStudentIDExists(allData.allStudents, studentCourse.studentID)) {
        throw std::invalid_argument("This student does not exist, please try again!");
    }

    if (checkStudentInCourse(
            allData.allStudentCourses, studentCourse.studentID, studentCourse.courseID,
            studentCourse.className
        )) {
        throw std::invalid_argument(
            "This student is already in the course, please try again!"
        );
    }

    saveStudentToCourse(studentCourse);
}

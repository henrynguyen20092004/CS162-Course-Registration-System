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

void addStudentToCourse() {
    StudentCourse studentCourse;
    bool validStudentCourse = false;

    do {
        try {
            inputStudentCourse(studentCourse);
            validateStudentCourse(
                allData.allStudents, allData.allClasses, allData.allCourses, studentCourse
            );

            if (checkStudentInCourse(
                    allData.allStudentCourses, studentCourse.studentID,
                    studentCourse.courseID, studentCourse.className
                )) {
                std::cout << "This student is already in the course, please try again!\n";
                continue;
            }

            validStudentCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validStudentCourse);

    saveStudentToCourse(studentCourse);
    std::cout << "Student successfully added!\n";
}

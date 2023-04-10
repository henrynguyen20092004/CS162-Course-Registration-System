#include "ViewStudentsInCourse.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../Check/CheckCourse/CheckCourse.h"
#include "../../GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../../InputAndValidate/InputAndValidateCourse/InputAndValidateCourse.h"
#include "../../SortAndOutputStudents/SortAndOutputStudents.h"
#include "../ViewStudentInfo/ViewStudentInfo.h"

void displayStudentsInCourse(
    std::ostream& out, Student* allStudentsArray, int arraySize
) {
    for (int i = 0; i < arraySize; ++i) {
        out << "\nThis is the student number " << i + 1 << ":\n";
        viewStudentInfo(allStudentsArray[i]);
    }
}

void viewStudentsInCourse() {
    Course course;
    bool validCourse = false;

    do {
        try {
            // inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allData.allCourses, course, false);
            validCourse = true;
        } catch (std::exception& error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    Node<Student>* allStudentsInCourse = getAllStudentsInCourse(course);

    if (!allStudentsInCourse) {
        std::cout << "There's no student in this course, please add some!\n";
    }

    sortAndOutputStudents(std::cout, allStudentsInCourse, &displayStudentsInCourse);
}

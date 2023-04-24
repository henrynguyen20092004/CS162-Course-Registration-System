#include "ViewCoursesOfStudent.h"

#include "../../GetAll/GetAllCoursesOfStudent/GetAllCoursesOfStudent.h"
#include "../ViewCourses/ViewCourses.h"

void viewCoursesOfStudent(const User &user, const Semester &semester) {
    if (semester.schoolYearName == "") {
        std::cout
            << "There's no semester at the moment, please change the current semester!\n";
        return;
    }

    Node<Course> *allCoursesOfStudent = getAllCoursesOfStudent(user.username, semester);
    int index = 0;

    if (!allCoursesOfStudent) {
        std::cout << "You have no courses at the moment!\n";
        return;
    }

    std::cout << "This is the list of your courses:\n";

    for (Node<Course> *curCourse = allCoursesOfStudent; curCourse;
         curCourse = curCourse->next) {
        std::cout << "This is course number " << ++index << ":\n";
        viewACourse(curCourse->data);
    }

    deleteLinkedList(allCoursesOfStudent);
}

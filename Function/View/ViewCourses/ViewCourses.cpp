#include "ViewCourses.h"

#include "../../Input/Input.h"
#include "../../OpenFile/OpenFile.h"

void viewACourse(const Course& course) {
    std::cout << "School year: " << course.schoolYearName << '\n';
    std::cout << "Semester number: " << course.semesterNumber << '\n';
    std::cout << "Course id: " << course.id << '\n';
    std::cout << "Course name: " << course.name << '\n';
    std::cout << "Class name: " << course.className << '\n';
    std::cout << "Teacher name: " << course.teacherName << '\n';
    std::cout << "Credits: " << course.credits << '\n';
    std::cout << "Maximum number of students: " << course.maxStudent << '\n';
    std::cout << "Day of week that the course is performed: " << course.dayOfWeek << '\n';
    std::cout << "The session that the course is performed: Session "
              << course.sessionNumber << "\n\n";
}

void viewCourses() {
    std::ifstream fin;
    readFile(fin, "Data/Course.txt");
    Course course;
    std::cout << "This is the list of all courses: " << '\n';
    int index = 0;

    while (fin.good()) {
        getline(fin, course.schoolYearName);

        if (!fin.good()) {
            break;
        }

        course.semesterNumber = intInput(fin);
        getline(fin, course.id);
        getline(fin, course.name);
        getline(fin, course.className);
        getline(fin, course.teacherName);
        course.credits = intInput(fin);
        course.maxStudent = intInput(fin);
        getline(fin, course.dayOfWeek);
        course.sessionNumber = intInput(fin);
        std::cout << "This is course number " << ++index << ":\n";
        viewACourse(course);
    }

    fin.close();
}

#include "ViewCourses.h"

#include "../../Struct/Course.h"
#include "../OpenFile/OpenFile.h"

void viewCourses() {
    std::ifstream fin;
    readFile(fin, "Data/Course.txt");
    Course course;
    std::string semesterNumber, credits, maxStudentNumber, sessionNumber;
    std::cout << "This is the list of all courses: " << '\n';
    int index = 1;

    while (fin.good()) {
        getline(fin, course.schoolYearName);

        if (!fin.good()) {
            break;
        }

        getline(fin, semesterNumber);
        getline(fin, course.id);
        getline(fin, course.name);
        getline(fin, course.className);
        getline(fin, course.teacherName);
        getline(fin, credits);
        getline(fin, maxStudentNumber);
        getline(fin, course.dayOfWeek);
        getline(fin, sessionNumber);
        std::cout << "This is course number " << index++ << ":\n";
        std::cout << "School year: " << course.schoolYearName << '\n';
        std::cout << "Semester number: " << semesterNumber << '\n';
        std::cout << "Course id: " << course.id << '\n';
        std::cout << "Course name: " << course.name << '\n';
        std::cout << "Class name: " << course.className << '\n';
        std::cout << "Teacher name: " << course.teacherName << '\n';
        std::cout << "Credits: " << credits << '\n';
        std::cout << "Maximum number of students: " << maxStudentNumber << '\n';
        std::cout << "Day of week that the course is performed: " << course.dayOfWeek
                  << '\n';
        std::cout << "The session that the course is performed: Session " << sessionNumber
                  << "\n\n";
    }

    fin.close();
}

#include "CreateCourse.h"

#include "../CheckClass/CheckClass.h"
#include "../CheckCourse/CheckCourse.h"
#include "../CheckDate/CheckDate.h"
#include "../CreateSemester/CreateSemester.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../Input/Input.h"

void inputCourse(Course &course, const Semester &semester) {
    Node<std::string> *allClassName = getAllClasses();
    Node<Course> *allCourse = getAllCourse();

    bool classNameExist, courseExist, validTeacherName,
        validMaxStudentNumber = false, validDayOfWeek = false, validSessionNumber = false,
        validCredits = false;

    do {
        do {
            std::cout << "Please enter the class name of the course: ";
            getline(std::cin, course.className);
            classNameExist = checkClassExists(allClassName, course.className);

            if (!classNameExist) {
                std::cout << "This class does not exist. Please try again!\n";
            }
        } while (!classNameExist);

        std::cout << "Please enter the course id: ";
        getline(std::cin, course.id);
        courseExist = checkCourseExists(allCourse, course.id, course.className);

        if (courseExist) {
            std::cout << "This course already exists, please try again!\n";
        }
    } while (courseExist);

    std::cout << "Please enter the course name: ";
    getline(std::cin, course.name);

    do {
        try {
            std::cout << "Please enter the teacher name: ";
            course.teacherName = nameInput();
            validTeacherName = true;
        } catch (std::exception &error) {
            std::cout << error.what();
            validTeacherName = false;
        }
    } while (!validTeacherName);

    do {
        try {
            std::cout << "Please enter the number of credits of this course: ";
            course.credits = intInput();
            validCredits = course.credits > 0;

            if (!validCredits) {
                std::cout << "Invalid credits number. Please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCredits);

    do {
        try {
            std::cout << "Please enter the maximum number of students in the course: ";
            course.maxStudent = intInput();
            validMaxStudentNumber = course.maxStudent > 0;

            if (!validMaxStudentNumber) {
                std::cout << "Invalid maximum number of students. Please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validMaxStudentNumber);

    do {
        std::cout << "Please choose the day of week that the course will be "
                     "perfomed (MON/TUE/WED/THU/FRI/SAT): ";
        getline(std::cin, course.dayOfWeek);

        for (char &x : course.dayOfWeek) {
            x = toupper(x);
        }

        validDayOfWeek = checkValidDayOfWeek(course.dayOfWeek);

        if (!validDayOfWeek) {
            std::cout << "Invalid day of week, please try again!\n";
        }
    } while (!validDayOfWeek);

    do {
        try {
            std::cout << "Please choose the session number that the course will be "
                         "perfomed: ";
            course.sessionNumber = intInput();
            validSessionNumber = course.sessionNumber > 0 && course.sessionNumber <= 4;

            if (!validSessionNumber) {
                std::cout << "Invalid session number, please try again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validSessionNumber);

    course.semesterNumber = semester.number;
    course.schoolYearName = semester.schoolYearName;

    deleteLinkedList(allClassName);
    deleteLinkedList(allCourse);
}

void saveCourse(Course course) {
    std::ofstream fout;
    writeFile(fout, "Data/Course.txt", std::ios::app);
    fout << course.schoolYearName << '\n';
    fout << course.semesterNumber << '\n';
    fout << course.id << '\n';
    fout << course.name << '\n';
    fout << course.className << '\n';
    fout << course.teacherName << '\n';
    fout << course.credits << '\n';
    fout << course.maxStudent << '\n';
    fout << course.dayOfWeek << '\n';
    fout << course.sessionNumber << '\n';
    fout.close();
    std::cout << "Course successfully added!\n";
}

void createCourse(const Semester &semester) {
    if (semester.schoolYearName == "") {
        std::cout << "Please create a semester first!\n";
        return;
    }

    Course course;
    inputCourse(course, semester);
    saveCourse(course);
}

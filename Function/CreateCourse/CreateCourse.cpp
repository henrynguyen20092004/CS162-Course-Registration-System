#include "CreateCourse.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../CreateSemester/CreateSemester.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../Input/Input.h"

void validateCourse(
    Node<Course> *allCourses, Node<std::string> *allClasses, const Course &course
) {
    if (!checkClassExists(allClasses, course.className)) {
        throw std::invalid_argument("This class does not exist. Please try again!\n");
    }

    if (checkCourseExists(allCourses, course.id, course.className)) {
        throw std::invalid_argument("This course already exists, please try again!\n");
    }

    if (course.credits < 1) {
        throw std::invalid_argument("Invalid credits number, please try again!\n");
    }

    if (course.maxStudent < 1) {
        throw std::invalid_argument(
            "Invalid maximum number of students, please try again!\n"
        );
    }

    if (!checkDayOfWeek(course.dayOfWeek)) {
        throw std::invalid_argument("Invalid day of week, please try again!\n");
    }

    if (course.sessionNumber < 1 || course.sessionNumber > 4) {
        throw std::invalid_argument("Invalid session number, please try again!\n");
    }
}

void inputCourse(Course &course) {
    std::cout << "Please enter the class name of the course: ";
    getline(std::cin, course.className);
    std::cout << "Please enter the course id: ";
    getline(std::cin, course.id);
    std::cout << "Please enter the course name: ";
    getline(std::cin, course.name);
    std::cout << "Please enter the teacher name: ";
    course.teacherName = nameInput();
    std::cout << "Please enter the number of credits of this course: ";
    course.credits = intInput();
    std::cout << "Please enter the maximum number of students in the course: ";
    course.maxStudent = intInput();
    std::cout << "Please choose the day of week that the course will be perfomed "
                 "(MON/TUE/WED/THU/FRI/SAT): ";
    getline(std::cin, course.dayOfWeek);
    std::cout << "Please choose the session number that the course will be perfomed: ";
    course.semesterNumber = intInput();
}

void saveCourse(const Course &course) {
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
        throw std::runtime_error("Please create a semester first!\n");
    }

    Node<Course> *allCourses = getAllCourses();
    Node<std::string> *allClasses = getAllClasses();
    Course course;
    bool validCourse = false;

    course.schoolYearName = semester.schoolYearName;
    course.semesterNumber = semester.number;

    do {
        try {
            inputCourse(course);
            validateCourse(allCourses, allClasses, course);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    saveCourse(course);
    deleteLinkedList(allCourses);
    deleteLinkedList(allClasses);
}

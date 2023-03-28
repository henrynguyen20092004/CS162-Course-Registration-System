#include "Function.h"

#include "Input/Input.h"
#include "OpenFile/OpenFile.h"

void displayUserCommand() {
    std::cout << "1. View my profile info\n"
              << "2. Change password\n"
              << "3. Log out\n"
              << "4. Exit the program\n";
}

void displayAdminCommand() {
    std::cout << "5. Create a school year\n"
              << "6. Create a class\n"
              << "7. Add a student to a class\n"
              << "8. Import a list of students in a class\n"
              << "9. Create a semester\n"
              << "10. Add a course to the semester\n"
              << "11. Import a list of students in a course\n"
              << "12. Update a course\n"
              << "13. Add a student to a course\n"
              << "14. Remove a student from a course\n"
              << "15. Delete a course\n"
              << "16. View all classes\n"
              << "17. View all students in a class\n"
              << "18. View all courses\n"
              << "19. View all students in a course\n"
              << "20. Export a list of students in a course\n"
              << "21. Import the scoreboard of a course\n"
              << "22. View the scoreboard of a course\n"
              << "23. Update a student's result\n"
              << "24. View the scoreboard of a class\n";
}

void displayStudentCommand() {
    std::cout << "5. View my courses\n"
              << "6. View my scoreboard\n";
}

void processUserCommand(int commandNumber, User &currentUser) {
    switch (commandNumber) {
        case 1: {
            viewProfileInfo(currentUser);
            break;
        }

        case 2: {
            changePassword(currentUser);
            break;
        }

        case 3: {
            logOut(currentUser);
            break;
        }
    }
}

void processAdminCommand(int commandNumber, Semester &currentSemester) {
    switch (commandNumber) {
        case 5: {
            createSchoolYear();
            break;
        }

        case 6: {
            createClass();
            break;
        }

        case 7: {
            createStudent();
            break;
        }

        case 8: {
            // Import students in a class function
            break;
        }

        case 9: {
            currentSemester = createSemester();
            break;
        }

        case 10: {
            createCourse(currentSemester);
            break;
        }

        case 11: {
            // Import students in a course function
            break;
        }

        case 12: {
            updateCourse();
            break;
        }

        case 13: {
            addStudentToCourse();
            break;
        }

        case 14: {
            removeStudentFromCourse();
            break;
        }

        case 15: {
            deleteCourse();
            break;
        }

        case 16: {
            viewClasses();
            break;
        }

        case 17: {
            viewStudentsInClass();
            break;
        }

        case 18: {
            viewCourses();
            break;
        }

        case 19: {
            viewStudentsInCourse();
            break;
        }

        case 20: {
            // Export students in a course function
            break;
        }

        case 21: {
            downloadPrompt("Scoreboard.csv", &importScoreboard);
            break;
        }

        case 22: {
            // View scoreboard of a course function
            break;
        }

        case 23: {
            // Update a student's result function
            break;
        }

        case 24: {
            // View scoreboard of a class function
            break;
        }
    }
}

void processStudentCommand(int commandNumber) {
    switch (commandNumber) {
        case 5: {
            // View student's courses function
            break;
        }

        case 6: {
            // View student's scoreboard function
            break;
        }
    }
}

Semester getCurrentSemester() {
    std::ifstream fin;
    readFile(fin, "Data/CurrentSemester.txt");
    Semester semester;
    fin >> semester.schoolYearName;
    fin >> semester.number;
    fin >> semester.startDate;
    fin >> semester.endDate;
    fin.close();
    return semester;
}

void menu() {
    User currentUser;
    Semester currentSemester = getCurrentSemester();
    int choice;

    do {
        try {
            if (currentUser.username == "") {
                currentUser = logIn();
            } else {
                std::cout << "\nWhat do you want to do?\n";
                displayUserCommand();
                int maxNumberOfCommand;

                if (currentUser.username == "admin") {
                    displayAdminCommand();
                    maxNumberOfCommand = 24;
                } else {
                    displayStudentCommand();
                    maxNumberOfCommand = 6;
                }

                std::cout << "Enter your choice: ";
                choice = intInput();
                std::cout << '\n';

                if (1 <= choice && choice <= 3) {
                    processUserCommand(choice, currentUser);
                } else if (5 <= choice && choice <= maxNumberOfCommand) {
                    if (currentUser.username == "admin") {
                        processAdminCommand(choice, currentSemester);
                    } else {
                        processStudentCommand(choice);
                    }
                } else if (choice != 4) {
                    std::cout << "Invalid option, please try again!\n";
                }
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (choice != 4);
}

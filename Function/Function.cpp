#include "Function.h"

#include "Input/Input.h"

void displayUserCommand() {
    std::cout << "1. View my profile info\n"
              << "2. Change password\n"
              << "3. Log out\n"
              << "4. Exit the program\n";
}

void displayAdminCommand() {
    std::cout << "5. Create a school year\n"
              << "6. Create a class\n"
              << "7. Add students to a class\n"
              << "8. Import a list of students in a class\n"
              << "9. Create a semester\n"
              << "10. Add a course to the semester\n"
              << "11. Import a list of students in a course\n"
              << "12. Update a course\n"
              << "13. Add a student to the course\n"
              << "14. Remove a student from the course\n"
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

void processUserCommand(int commandNumber, User &currentUser, bool &loop) {
    switch (commandNumber) {
        case 1: {
            // View profile info function
            break;
        }

        case 2: {
            changePassword(currentUser);
            break;
        }

        case 3: {
            // Log out function
            break;
        }

        case 4: {
            loop = false;
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
            // Create class function
            break;
        }

        case 7: {
            // Add students to class function
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
            // Add a course to the semester function
            break;
        }

        case 11: {
            // Import students in a course function
            break;
        }

        case 12: {
            // Update course function
            break;
        }

        case 13: {
            // Add a student to the course function
            break;
        }

        case 14: {
            // Remove a student from the course function
            break;
        }

        case 15: {
            // Delete course function
            break;
        }

        case 16: {
            viewClasses();
            break;
        }

        case 17: {
            // View students in a class function
            break;
        }

        case 18: {
            // View all courses function
            break;
        }

        case 19: {
            // View students in a course function
            break;
        }

        case 20: {
            // Export students in a course function
            break;
        }

        case 21: {
            // Import scoreboard of a course function
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

void menu() {
    User currentUser;
    Semester currentSemester;
    bool loop = true;

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
                int input = intInput();
                std::cout << '\n';

                if (1 <= input && input <= 4) {
                    processUserCommand(input, currentUser, loop);
                } else if (5 <= input && input <= maxNumberOfCommand) {
                    if (currentUser.username == "admin") {
                        processAdminCommand(input, currentSemester);
                    } else {
                        processStudentCommand(input);
                    }
                } else {
                    std::cout << "Invalid option, please try again!\n";
                }
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (loop);
}
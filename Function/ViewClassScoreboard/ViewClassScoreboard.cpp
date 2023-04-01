#include "ViewClassScoreboard.h"

#include <iomanip>

#include "../../Struct/LinkedList.h"
#include "../Check/CheckClass/CheckClass.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"

void viewScoreboardTable(Node<Student>* allStudentsInClass) {
    Node<Student>* cur = allStudentsInClass;
    std::cout << std::setw(15);
    std::cout << "Student ID";
    std::cout << std::setw(10);
    std::cout << "First Name";
    while (cur) {
        std::cout << std::setw(15);
        std::cout << cur->data.id << '\n';
        std::cout << std::setw(10);
        std::cout << cur->data.firstName << '\n';

        cur = cur->next;
    }
}

void viewClassScoreboard() {
    Node<std::string>* allClasses = getAllClasses();
    std::string className;
    bool classExists;

    do {
        std::cout << "Enter the class you want to view scoreboard";
        getline(std::cin, className);
        classExists = checkClassExists(allClasses, className);

        if (!classExists) {
            std::cout << "This class doesn't exists, please try again!\n";
        }
    } while (!classExists);

    Node<Student>* allStudentsInClass = getAllStudentsInClass(className);

    if (!allStudentsInClass) {
        std::cout << "There's no student in this class!\n";
    }

    viewScoreboardTable(allStudentsInClass);

    deleteLinkedList(allClasses);
    deleteLinkedList(allStudentsInClass);
}
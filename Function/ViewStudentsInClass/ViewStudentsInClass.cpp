#include "ViewStudentsInClass.h"

#include "../Check/CheckClass/CheckClass.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"
#include "../SortAndDisplayStudent/SortAndDisplayStudent.h"

void viewStudentsInClass() {
    Node<std::string>* allClasses = getAllClasses();
    std::string className;
    bool classExists;

    do {
        std::cout << "Please enter the class' name: ";
        getline(std::cin, className);
        classExists = checkClassExists(allClasses, className);

        if (!classExists) {
            std::cout << "This class doesn't exists, please create it or try again!\n";
        }
    } while (!classExists);

    Node<Student>* allStudentsInClass = getAllStudentsInClass(className);

    if (!allStudentsInClass) {
        std::cout << "There's no student in this class!\n";
    }

    sortAndDisplayStudent(allStudentsInClass);
    deleteLinkedList(allClasses);
}

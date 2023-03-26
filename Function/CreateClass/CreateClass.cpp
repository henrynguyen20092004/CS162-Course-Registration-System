#include "CreateClass.h"

#include "../CheckClass/CheckClass.h"
#include "../GetAllClasses/GetAllClasses.h"
#include "../OpenFile/OpenFile.h"

std::string inputClassName(Node<std::string>*& allClassNames) {
    std::string className;
    bool classExists;

    do {
        std::cout << "Please enter the name of the class: ";
        getline(std::cin, className);
        classExists = checkClassExists(allClassNames, className);

        if (classExists) {
            std::cout << "This class already exists, please try again!\n";
        }
    } while (classExists);

    return className;
}

void saveClassName(const std::string& className) {
    std::ofstream fout;
    writeFile(fout, "Data/Class.txt", std::ios::app);
    fout << className << '\n';
    std::cout << "Added the class " << className << " successfully!\n";
    fout.close();
}

void createClass() {
    Node<std::string>* allClasses = getAllClasses();
    std::string className = inputClassName(allClasses);
    saveClassName(className);
    deleteLinkedList(allClasses);
}

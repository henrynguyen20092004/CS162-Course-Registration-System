#include "CreateClass.h"

#include "../GetAllClassNames/GetAllClassNames.h"
#include "../OpenFile/OpenFile.h"

bool checkExistedClass(Node<std::string>* allClassNames, const std::string& className) {
    while (allClassNames) {
        if (allClassNames->data == className) {
            return true;
        }

        allClassNames = allClassNames->next;
    }

    return false;
}

std::string inputClassName(Node<std::string>*& allClassNames) {
    std::string className;
    bool availableClassName;

    do {
        std::cout << "Please enter the name of the class: ";
        getline(std::cin, className);
        availableClassName = checkExistedClass(allClassNames, className);

        if (availableClassName) {
            std::cout << "This class already exists, please try again!\n";
        }
    } while (availableClassName);

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
    Node<std::string>* allClassNames = getAllClassNames();
    std::string className = inputClassName(allClassNames);
    saveClassName(className);
    deleteLinkedList(allClassNames);
}

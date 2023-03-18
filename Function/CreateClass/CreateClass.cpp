#include "CreateClass.h"

#include "../GetAllClassNames/GetAllClassNames.h"
#include "../OpenFile/OpenFile.h"

bool checkClassExists(Node<std::string>* allClass, const std::string& className) {
    while (allClass) {
        if (allClass->data == className) {
            return true;
        }
        allClass = allClass->next;
    }
    return false;
}

std::string inputClassName(Node<std::string>*& allClass) {
    std::string className;
    do {
        std::cout << "Please enter the name of the class: ";
        getline(std::cin, className);
    } while (checkClassExists(allClass, className));
    return className;
}

void saveClassName(const std::string& className) {
    std::ofstream fout;
    writeFile(fout, "Data/Class.txt", std::ios::app);
    {
        fout << className << '\n';
        std::cout << "Add the class " << className << " successfully!\n";
    }
    fout.close();
}

void createClass() {
    Node<std::string>* allClass = getAllClassNames();
    std::string className = inputClassName(allClass);
    saveClassName(className);
}

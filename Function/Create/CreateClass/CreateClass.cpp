#include "CreateClass.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"

void validateClass(Node<std::string>* allClasses, const std::string& className) {
    if (checkClassExists(allClasses, className)) {
        throw std::invalid_argument("This class already exists, please try again!");
    }
}

void inputClass(std::string& className) {
    std::cout << "Please enter the name of the class: ";
    getline(std::cin, className);
}

void saveClass(const std::string& className) {
    std::ofstream fout;
    writeFile(fout, "Data/Class.txt", std::ios::app);
    fout << className << '\n';
    fout.close();
    addNewItemsToOldList(allData.allClasses, new Node(className));
}

void createClass() {
    std::string className;
    bool validClass = false;

    do {
        try {
            inputClass(className);
            validateClass(allData.allClasses, className);
            validClass = true;
        } catch (std::exception& error) {
            std::cout << error.what();
        }
    } while (!validClass);

    saveClass(className);
    std::cout << "Class successfully added!\n";
}

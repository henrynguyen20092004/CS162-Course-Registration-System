#include "CreateClass.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"

void validateClass(Node<std::string>* allClasses, const std::string& className) {
    if (checkClassExists(allClasses, className)) {
        throw std::invalid_argument("This class already exists, please try again!");
    }
}

void saveClass(const std::string& className) {
    std::ofstream fout;
    writeFile(fout, "Data/Class.txt", std::ios::app);
    fout << className << '\n';
    fout.close();
    addNewItemsToOldList(allData.allClasses, new Node(className));
}

void createClass(char* inputedClassName) {
    std::string className = inputedClassName;
    validateClass(allData.allClasses, className);
    saveClass(className);
}

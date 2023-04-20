#include "CreateClass.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"

void validateClass(Node<std::string>* allClasses, const std::string& className) {
    int classNameLength = className.size();

    for (int i = 0; i < classNameLength; ++i) {
        if (!isalnum(className[i])) {
            throw std::invalid_argument("Invalid class name, please try again!");
        }
    }

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

void createClass(char* inputtedClassName) {
    std::string className = inputtedClassName;
    validateClass(allData.allClasses, className);
    saveClass(className);
}

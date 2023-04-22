#include "CreateClass.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"

void saveClass(const std::string& className) {
    std::ofstream fout;
    writeFile(fout, "Data/Class.txt", std::ios::app);
    fout << className << '\n';
    fout.close();
    addNewItemsToOldList(allData.allClasses, new Node(className));
}

void createClass(char* inputtedClassName) {
    std::string className = inputtedClassName;

    if (checkClassExists(allData.allClasses, className)) {
        throw std::invalid_argument("This class already exists, please try again!");
    }

    saveClass(className);
}

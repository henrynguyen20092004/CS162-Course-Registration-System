#include "CreateClass.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckClass/CheckClass.h"

void saveClass(const std::string& className) {
    std::ofstream fout;
    writeFile(fout, "Data/Class.txt", std::ios::app);
    fout << className << '\n';
    fout.close();
    addNewItemsToOldList(GlobalVar::allData.allClasses, new Node(className));
}

void createClass(char* inputtedClassName) {
    if (checkClassExists(GlobalVar::allData.allClasses, inputtedClassName)) {
        throw std::invalid_argument("This class already exists, please try again!");
    }

    saveClass(inputtedClassName);
}

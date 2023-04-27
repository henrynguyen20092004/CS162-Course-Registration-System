#include "ImportStudentsInClassPage.h"

#include "../../../Function/ImportCSV/ImportScoreboard/ImportScoreboard.h"
#include "../../../Function/ImportCSV/ImportStudentsInClass/ImportStudentsInClass.h"
#include "../../../Struct/Data.h"
#include "../ImportCSVPage.h"

class ImportStudentsInClassPage : public ImportCSVPage {
   private:
    void initInputs() override;

   public:
    using ImportCSVPage::ImportCSVPage;
    std::string className;
};

void ImportStudentsInClassPage::initInputs() {
    ImportCSVPage::initInputs();
    dropDowns[1] = DropDown("Class name", allData.allClasses, inputPos[2], inputWidth);
}

void importStudentsInClassPage(const std::string& className) {
    ImportStudentsInClassPage importStudentsInClassPage(
        "Import students in a class", "StudentsInClass.csv", &importStudentsInClass
    );
    importStudentsInClassPage.className = className;

    importStudentsInClassPage.mainLoop();
}

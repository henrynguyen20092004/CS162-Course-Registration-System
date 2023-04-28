#include "ImportStudentsInClassPage.h"

#include "../../../Function/ImportCSV/ImportStudentsInClass/ImportStudentsInClass.h"
#include "../ImportCSVPage.h"

class ImportStudentsInClassPage : public ImportCSVPage {
   public:
    using ImportCSVPage::ImportCSVPage;
    std::string className;
};

void importStudentsInClassPage(const std::string& className) {
    ImportStudentsInClassPage importStudentsInClassPage(
        "Import students of class " + className, "StudentsInClass.csv", className,
        &importStudentsInClass, VIEW_STUDENTS_IN_CLASS
    );
    importStudentsInClassPage.mainLoop();
}

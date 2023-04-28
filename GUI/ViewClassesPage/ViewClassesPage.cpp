#include "ViewClassesPage.h"

#include "../../Struct/Data.h"
#include "../TablePage/TablePage.h"

class ViewClassesPage : public TablePage<std::string> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewClassesPage::initColumns() {
    columnTitle = new std::string[col]{"No", "Class"};
    columnWidths = new float[col + buttonCol]{
        150.0f, 400.0f, TABLE_BUTTON_CELL_WIDTH, TABLE_BUTTON_CELL_WIDTH};
}

void ViewClassesPage::initButtons() {
    headerButtonTitles[0] = "Create a class";
    firstRowButtonTitles[0] = "Student";
    firstRowButtonTitles[1] = "Score";
}

void ViewClassesPage::convertLinkedListToData() {
    std::string* allClassesArray;
    createAndSortDataArray(allClassesArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = allClassesArray[i - 1];
    }

    delete[] allClassesArray;
}

void viewClassesPage() {
    ViewClassesPage viewClassesPage("All classes", 2, 2, 1, allData.allClasses);
    viewClassesPage.mainLoop();
}

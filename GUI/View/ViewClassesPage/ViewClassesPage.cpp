#include "ViewClassesPage.h"

#include "../../TablePage/TablePage.h"

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
    firstRowButtonTitles[0] = "Students";
    firstRowButtonTitles[1] = "Score";
    headerButtonCommands = new Command[headerButton]{CREATE_CLASS};
    columnButtonCommands =
        new Command[buttonCol]{VIEW_STUDENTS_IN_CLASS, VIEW_SCOREBOARD_OF_CLASS};
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
    ViewClassesPage viewClassesPage(
        "List of classes", 2, 2, 1, GlobalVar::allData.allClasses
    );
    viewClassesPage.mainLoop();
}

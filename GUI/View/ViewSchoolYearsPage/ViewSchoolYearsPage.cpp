#include "ViewSchoolYearsPage.h"

#include "../../../Struct/Data.h"
#include "../../TablePage/TablePage.h"

class ViewSchoolYearsPage : public TablePage<std::string> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewSchoolYearsPage::initColumns() {
    columnTitle = new std::string[col]{"No", "School year"};
    columnWidths = new float[col]{150.0f, 400.0f};
}

void ViewSchoolYearsPage::initButtons() {
    headerButtonTitles[0] = "Create a school year";
    headerButtonCommands = new Command{CREATE_SCHOOL_YEAR};
}

void ViewSchoolYearsPage::convertLinkedListToData() {
    std::string* allSchoolYearsArray;
    createAndSortDataArray(allSchoolYearsArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = allSchoolYearsArray[i - 1];
    }

    delete[] allSchoolYearsArray;
}

void viewSchoolYearsPage() {
    ViewSchoolYearsPage viewSchoolYearsPage(
        "List of school years", 2, 0, 1, allData.allSchoolYears
    );
    viewSchoolYearsPage.mainLoop();
}

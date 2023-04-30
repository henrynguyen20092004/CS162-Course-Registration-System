#include "ViewSemestersPage.h"

#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../TablePage/TablePage.h"

class ViewSemestersPage : public TablePage<Semester> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewSemestersPage::initColumns() {
    columnTitle =
        new std::string[col]{"No", "School Year", "Start Date", "End Date", "Semeters"};
    columnWidths = new float[col]{
        150.0f, 200.0f, 200.0f, 200.0f, 200.0f,
    };
}

void ViewSemestersPage::initButtons() {
    headerButtonTitles[0] = "Create a semester";
    headerButtonCommands = new Command[headerButton]{CREATE_SEMESTER};
}

void ViewSemestersPage::convertLinkedListToData() {
    Semester* allSemestersArray;
    createAndSortDataArray(allSemestersArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = allSemestersArray[i - 1].schoolYearName;
        tableData[i][2] = allSemestersArray[i - 1].startDate;
        tableData[i][3] = allSemestersArray[i - 1].endDate;
        tableData[i][4] = std::to_string(allSemestersArray[i - 1].number);
    }

    delete[] allSemestersArray;
}

void viewSemestersPage() {
    ViewSemestersPage viewSemestersPage(
        "List of semesters", 5, 0, 1, GlobalVar::allData.allSemesters
    );
    viewSemestersPage.mainLoop();
}

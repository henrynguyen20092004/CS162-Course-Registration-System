#include "ViewScoreboardOfStudentPage.h"

#include "../../../Function/CheckAndConvertString/CheckAndConvertString.h"
#include "../../../Function/GetAll/GetAllScores/GetAllScores.h"
#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../TablePage/TablePage.h"

class ViewScoreboardOfStudentPage : public TablePage<Score> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewScoreboardOfStudentPage::initColumns() {
    columnTitle = new std::string[col]{"No",         "Course",     "Midterm mark",
                                       "Other mark", "Final mark", "Total mark"};
    columnWidths = new float[col]{50.0f, 250.0f, 150.0f, 150.0f, 150.0f, 150.0f};
}

void ViewScoreboardOfStudentPage::convertLinkedListToData() {
    Score* studentScoresArray;
    createAndSortDataArray(studentScoresArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = studentScoresArray[i - 1].studentCourse.courseID + '-' +
                          studentScoresArray[i - 1].studentCourse.className;
        tableData[i][2] = convertScoreToString(studentScoresArray[i - 1].midtermMark);
        tableData[i][3] = convertScoreToString(studentScoresArray[i - 1].otherMark);
        tableData[i][4] = convertScoreToString(studentScoresArray[i - 1].finalMark);
        tableData[i][5] = convertScoreToString(studentScoresArray[i - 1].totalMark);
    }

    deleteLinkedList(dataLinkedList);
    delete[] studentScoresArray;
}

void viewScoreboardOfStudentPage() {
    ViewScoreboardOfStudentPage viewScoreboardOfStudentPage(
        "Your scores this semester", 6, 0, 0, getAllScoresOfCurrentStudent()
    );
    viewScoreboardOfStudentPage.mainLoop();
}

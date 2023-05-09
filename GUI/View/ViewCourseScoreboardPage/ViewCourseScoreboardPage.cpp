#include "ViewCourseScoreBoardPage.h"

#include "../../../API/CheckAndConvertString/CheckAndConvertString.h"
#include "../../../API/GetAll/GetAllScores/GetAllScores.h"
#include "../../../API/OperatorOverload/OperatorOverload.h"
#include "../../TablePage/TablePage.h"

class ViewCourseScoreBoardPage : public TablePage<Score> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewCourseScoreBoardPage::initColumns() {
    columnTitle = new std::string[col]{
        "No", "ID", "Name", "Midterm mark", "Other mark", "Final mark", "Total mark"};
    columnWidths = new float[col]{
        50.0f, 200.0f, 250.0f, 150.0f, 150.0f, 150.0f, 150.0f,
    };
}

void ViewCourseScoreBoardPage::initButtons() {
    headerButtonTitles[0] = "Import CSV of scoreboard";
    headerButtonTitles[1] = "Update a student's result";
    headerButtonCommands =
        new Command[headerButton]{IMPORT_SCOREBOARD, UPDATE_STUDENT_RESULT};
}

void ViewCourseScoreBoardPage::convertLinkedListToData() {
    Score* courseScoreboardArray;
    createAndSortDataArray(courseScoreboardArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = courseScoreboardArray[i - 1].studentCourse.studentID;
        tableData[i][2] = courseScoreboardArray[i - 1].studentFullName;
        tableData[i][3] = convertScoreToString(courseScoreboardArray[i - 1].midtermMark);
        tableData[i][4] = convertScoreToString(courseScoreboardArray[i - 1].otherMark);
        tableData[i][5] = convertScoreToString(courseScoreboardArray[i - 1].finalMark);
        tableData[i][6] = convertScoreToString(courseScoreboardArray[i - 1].totalMark);
    }

    deleteLinkedList(dataLinkedList);
    delete[] courseScoreboardArray;
}

void viewCourseScoreboardPage(const std::string& courseIDAndClassName) {
    ViewCourseScoreBoardPage viewCourseScoreboardPage(
        "Scoreboard of course " + courseIDAndClassName, 7, 0, 2,
        getAllScoresOfStudentsInCourse(courseIDAndClassName)
    );

    viewCourseScoreboardPage.mainLoop();
}

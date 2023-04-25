#include "ViewCourseScoreBoardPage.h"

#include <math.h>

#include "../../Function/ConvertScoreToString/ConvertScoreToString.h"
#include "../../Function/GetAll/GetAllScoresOfStudentsInCourse/GetAllScoresOfStudentsInCourse.h"
#include "../../Function/OperatorOverload/OperatorOverload.h"
#include "../TablePage/TablePage.h"

class ViewCourseScoreBoardPage : public TablePage<Score> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewCourseScoreBoardPage::initColumns() {
    columnTitle =
        new std::string[col]{"No", "ID", "Name", "Mid-term", "Final", "Other", "Total"};
    columnWidths = new float[col]{50, 200, 300, 150, 150, 150, 150};
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
        tableData[i][4] = convertScoreToString(courseScoreboardArray[i - 1].finalMark);
        tableData[i][5] = convertScoreToString(courseScoreboardArray[i - 1].otherMark);
        tableData[i][6] = convertScoreToString(courseScoreboardArray[i - 1].totalMark);
    }

    deleteLinkedList(dataLinkedList);
    delete[] courseScoreboardArray;
}

void viewCourseScoreboardPage(const std::string& courseIDAndClassName) {
    ViewCourseScoreBoardPage viewCourseScoreboardPage(
        courseIDAndClassName + " scoreboard:", 7,
        getAllScoresOfStudentsInCourse(courseIDAndClassName)
    );

    viewCourseScoreboardPage.mainLoop();
}

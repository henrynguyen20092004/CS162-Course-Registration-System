#include "ViewScoreboardOfStudentPage.h"

#include "../../Function/ConvertScoreToString/ConvertScoreToString.h"
#include "../../Function/GetAll/GetAllScoresOfStudent/GetAllScoresOfStudent.h"
#include "../../Function/OperatorOverload/OperatorOverload.h"
#include "../TablePage/TablePage.h"

class ViewScoreboardOfStudentPage : public TablePage<Score> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewScoreboardOfStudentPage::initColumns() {
    columnTitle = new std::string[col]{
        "No", "Course ID-Class name", "Midterm", "Final", "Other", "Total"};
    columnWidths = new float[col]{50, 250, 150, 150, 150, 150};
}

void ViewScoreboardOfStudentPage::convertLinkedListToData() {
    Score* studentScoreboardArray;
    createAndSortDataArray(studentScoreboardArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = studentScoreboardArray[i - 1].studentCourse.courseID + '-' +
                          studentScoreboardArray[i - 1].studentCourse.className;
        tableData[i][2] = convertScoreToString(studentScoreboardArray[i - 1].midtermMark);
        tableData[i][3] = convertScoreToString(studentScoreboardArray[i - 1].finalMark);
        tableData[i][4] = convertScoreToString(studentScoreboardArray[i - 1].otherMark);
        tableData[i][5] = convertScoreToString(studentScoreboardArray[i - 1].totalMark);
    }

    deleteLinkedList(dataLinkedList);
    delete[] studentScoreboardArray;
}

void viewScoreboardOfStudentPage(
    const std::string& studentID, const Semester& currentSemester
) {
    ViewScoreboardOfStudentPage viewScoreboardOfStudentPage(
        "Your scores this semester", 6, getAllScoresOfStudent(studentID, currentSemester)
    );

    viewScoreboardOfStudentPage.mainLoop();
}

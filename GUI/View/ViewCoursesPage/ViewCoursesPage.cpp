#include "ViewCoursesPage.h"

#include "../../../Function/GetAll/GetAllCourses/GetAllCourses.h"
#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../../Struct/Data.h"
#include "../../TablePage/TablePage.h"

class ViewCoursesPage : public TablePage<Course> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewCoursesPage::initColumns() {
    columnTitle =
        new std::string[col]{"No",      "Course",           "Course name", "Teacher name",
                             "Credits", "Maximum students", "Day",         "Session"};
    columnWidths = new float[col + buttonCol]{
        50.0f,
        180.0f,
        200.0f,
        180.0f,
        80.0f,
        180.0f,
        80.0f,
        80.0f,
        TABLE_BUTTON_CELL_WIDTH,
        TABLE_BUTTON_CELL_WIDTH};
}

void ViewCoursesPage::initButtons() {
    headerButtonTitles[0] = "Create a course";
    headerButtonTitles[1] = "Update a course";
    headerButtonTitles[2] = "Delete a course";
    firstRowButtonTitles[0] = "Student";
    firstRowButtonTitles[1] = "Score";
    headerButtonCommands =
        new Command[headerButton]{CREATE_COURSE, UPDATE_COURSE, DELETE_COURSE};
    columnButtonCommands =
        new Command[buttonCol]{VIEW_STUDENTS_IN_COURSE, VIEW_SCOREBOARD_OF_COURSE};
}

void ViewCoursesPage::convertLinkedListToData() {
    Course* courseArray;
    createAndSortDataArray(courseArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = courseArray[i - 1].id + '-' + courseArray[i - 1].className;
        tableData[i][2] = courseArray[i - 1].name;
        tableData[i][3] = courseArray[i - 1].teacherName;
        tableData[i][4] = std::to_string(courseArray[i - 1].credits);
        tableData[i][5] = std::to_string(courseArray[i - 1].maxStudent);
        tableData[i][6] = courseArray[i - 1].dayOfWeek;
        tableData[i][7] = std::to_string(courseArray[i - 1].sessionNumber);
    }

    delete[] courseArray;
}

void viewCoursesPage() {
    ViewCoursesPage viewCoursesPage("List of courses", 8, 2, 3, allData.allCourses);
    viewCoursesPage.mainLoop();
}

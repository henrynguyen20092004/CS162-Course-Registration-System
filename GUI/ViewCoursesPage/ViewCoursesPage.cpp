#include "ViewCoursesPage.h"

#include <algorithm>
#include <cstring>

#include "../../Function/GetAll/GetAllCourses/GetAllCourses.h"
#include "../../Function/OperatorOverload/OperatorOverload.h"
#include "../TablePage/TablePage.h"

class ViewCoursesPage : public TablePage<Course> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewCoursesPage::initColumns() {
    columnTitle = new std::string[col]{
        "No",
        "Course id",
        "Course name",
        "Class name",
        "Teacher name",
        "Credits",
        "Maximum students",
        "The day-performed",
        "The session-performed"};

    columnWidths = new float[col]{50, 100, 330, 120, 300, 100, 180, 190, 220};
}

void ViewCoursesPage::convertLinkedListToData() {
    Course* courseArray;
    createAndSortDataArray(courseArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = courseArray[i - 1].id;
        tableData[i][2] = courseArray[i - 1].name;
        tableData[i][3] = courseArray[i - 1].className;
        tableData[i][4] = courseArray[i - 1].teacherName;
        tableData[i][5] = std::to_string(courseArray[i - 1].credits);
        tableData[i][6] = std::to_string(courseArray[i - 1].maxStudent);
        tableData[i][7] = courseArray[i - 1].dayOfWeek;
        tableData[i][8] = std::to_string(courseArray[i - 1].sessionNumber);
    }

    deleteLinkedList(dataLinkedList);
    delete[] courseArray;
}

void viewCoursesPage() {
    ViewCoursesPage viewCoursesPage("List of cousres", 9, getAllCourses());
    viewCoursesPage.mainLoop();
}

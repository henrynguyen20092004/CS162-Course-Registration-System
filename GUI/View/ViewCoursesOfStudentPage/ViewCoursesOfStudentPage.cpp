#include "ViewCoursesOfStudentPage.h"

#include "../../../Function/GetAll/GetAllCourses/GetAllCourses.h"
#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../TablePage/TablePage.h"

class ViewCoursesOfStudentPage : public TablePage<Course> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewCoursesOfStudentPage::initColumns() {
    columnTitle =
        new std::string[col]{"No",      "Course",           "Course name", "Teacher name",
                             "Credits", "Maximum students", "Day",         "Session"};
    columnWidths = new float[col]{
        50.0f, 180.0f, 200.0f, 180.0f, 80.0f, 180.0f, 80.0f, 80.0f,
    };
}

void ViewCoursesOfStudentPage::convertLinkedListToData() {
    Course* coursesOfStudentArray;
    createAndSortDataArray(coursesOfStudentArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = coursesOfStudentArray[i - 1].id + '-' +
                          coursesOfStudentArray[i - 1].className;
        tableData[i][2] = coursesOfStudentArray[i - 1].name;
        tableData[i][3] = coursesOfStudentArray[i - 1].teacherName;
        tableData[i][4] = std::to_string(coursesOfStudentArray[i - 1].credits);
        tableData[i][5] = std::to_string(coursesOfStudentArray[i - 1].maxStudent);
        tableData[i][6] = coursesOfStudentArray[i - 1].dayOfWeek;
        tableData[i][7] = std::to_string(coursesOfStudentArray[i - 1].sessionNumber);
    }

    deleteLinkedList(dataLinkedList);
    delete[] coursesOfStudentArray;
}

void viewCoursesOfStudentPage() {
    ViewCoursesOfStudentPage viewCoursesOfStudentPage(
        "Your courses this semester", 8, 0, 0,
        getAllCoursesOfStudent(currentUser.username, currentSemester)
    );
    viewCoursesOfStudentPage.mainLoop();
}

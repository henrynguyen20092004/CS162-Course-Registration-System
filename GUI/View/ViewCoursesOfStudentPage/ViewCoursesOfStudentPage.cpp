#include "ViewCoursesOfStudentPage.h"

#include "../../../Function/GetAll/GetAllCoursesOfStudent/GetAllCoursesOfStudent.h"
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
    columnTitle = new std::string[col]{"No",           "Course ID", "Course name",
                                       "Class name",   "Teacher",   "Credits",
                                       "Max-students", "Day",       "Session"};
    columnWidths = new float[col]{50, 100, 300, 120, 300, 70, 125, 80, 80};
}

void ViewCoursesOfStudentPage::convertLinkedListToData() {
    Course* coursesOfStudentArray;
    createAndSortDataArray(coursesOfStudentArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = coursesOfStudentArray[i - 1].id;
        tableData[i][2] = coursesOfStudentArray[i - 1].name;
        tableData[i][3] = coursesOfStudentArray[i - 1].className;
        tableData[i][4] = coursesOfStudentArray[i - 1].teacherName;
        tableData[i][5] = std::to_string(coursesOfStudentArray[i - 1].credits);
        tableData[i][6] = std::to_string(coursesOfStudentArray[i - 1].maxStudent);
        tableData[i][7] = coursesOfStudentArray[i - 1].dayOfWeek;
        tableData[i][8] = std::to_string(coursesOfStudentArray[i - 1].sessionNumber);
    }

    deleteLinkedList(dataLinkedList);
    delete[] coursesOfStudentArray;
}

void viewCoursesOfStudentPage() {
    ViewCoursesOfStudentPage viewCoursesOfStudentPage(
        "All courses in this semester", 9, 0, 0,
        getAllCoursesOfStudent(currentUser.username, currentSemester)
    );

    viewCoursesOfStudentPage.mainLoop();
}

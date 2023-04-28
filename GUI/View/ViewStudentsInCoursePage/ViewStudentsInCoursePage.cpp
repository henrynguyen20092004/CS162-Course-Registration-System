#include "ViewStudentsInCoursePage.h"

#include "../../../Function/GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../../Function/SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"
#include "../../TablePage/TablePage.h"

class ViewStudentsInCoursePage : public TablePage<Student> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewStudentsInCoursePage::initColumns() {
    columnTitle =
        new std::string[col]{"No",     "Student ID",    "First Name", "Last Name",
                             "Gender", "Date of Birth", "Social ID"};
    columnWidths = new float[col]{50.0f, 200.0f, 120.0f, 330.0f, 80.0f, 180.0f, 150.0f};
}
void ViewStudentsInCoursePage::initButtons() {
    headerButtonTitles[0] = "Import CSV of students";
    headerButtonTitles[1] = "Export CSV of students";
    headerButtonCommands =
        new Command[headerButton]{IMPORT_STUDENTS_IN_COURSE, EXPORT_STUDENTS_IN_COURSE};
}

void ViewStudentsInCoursePage::convertLinkedListToData() {
    Student* studentInCourseArray;
    createAndSortDataArray(studentInCourseArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = studentInCourseArray[i - 1].id;
        tableData[i][2] = studentInCourseArray[i - 1].firstName;
        tableData[i][3] = studentInCourseArray[i - 1].lastName;
        tableData[i][4] = studentInCourseArray[i - 1].gender;
        tableData[i][5] = studentInCourseArray[i - 1].dateOfBirth;
        tableData[i][6] = studentInCourseArray[i - 1].socialID;
    }

    deleteLinkedList(dataLinkedList);
    delete[] studentInCourseArray;
}

void viewStudentsInCoursePage(const std::string& course) {
    std::string* courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, course);
    Course curCourse;
    curCourse.id = courseIDAndClassName[0];
    curCourse.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

    ViewStudentsInCoursePage viewStudentsInCoursePage(
        "All student in course " + course, 7, 0, 2, getAllStudentsInCourse(curCourse)
    );
    viewStudentsInCoursePage.mainLoop();
}

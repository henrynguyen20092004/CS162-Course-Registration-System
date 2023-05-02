#include "ViewStudentsInCoursePage.h"

#include "../../../Function/GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../../Function/RemoveStudentFromCourse/RemoveStudentFromCourse.h"
#include "../../../Function/SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"
#include "../../TablePage/TablePage.h"

class ViewStudentsInCoursePage : public TablePage<Student> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;
    void drawColumnButtons() override;

   public:
    ViewStudentsInCoursePage(const std::string& course, const Course& curCourse);
    Course curCourse;
};

ViewStudentsInCoursePage::ViewStudentsInCoursePage(
    const std::string& course, const Course& curCourse
)
    : TablePage(
          "All student in course " + course, 7, 1, 3, getAllStudentsInCourse(curCourse)
      ),
      curCourse(curCourse) {}

void ViewStudentsInCoursePage::initColumns() {
    columnTitle =
        new std::string[col]{"No",     "Student ID",    "First Name", "Last Name",
                             "Gender", "Date of Birth", "Social ID"};
    columnWidths = new float[col + buttonCol]{
        50.0f, 200.0f, 120.0f, 330.0f, 80.0f, 180.0f, 150.0f, TABLE_BUTTON_CELL_WIDTH};
}
void ViewStudentsInCoursePage::initButtons() {
    headerButtonTitles[0] = "Add a student to course";
    headerButtonTitles[1] = "Import CSV of students";
    headerButtonTitles[2] = "Export CSV of students";
    firstRowButtonTitles[0] = "Remove";
    headerButtonCommands = new Command[headerButton]{
        ADD_STUDENT_TO_COURSE, IMPORT_STUDENTS_IN_COURSE, EXPORT_STUDENTS_IN_COURSE};
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

void ViewStudentsInCoursePage::drawColumnButtons() {
    for (int i = 0; i < row - 1; ++i) {
        if (columnButtons[i][0].drawButton(scroll.y)) {
            removeStudentFromCourse(tableData[i + 1][1], curCourse);
            stopLoop = true;
        }
    }
}

void viewStudentsInCoursePage(const std::string& course) {
    std::string* courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, course);
    Course curCourse;
    curCourse.id = courseIDAndClassName[0];
    curCourse.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

    ViewStudentsInCoursePage viewStudentsInCoursePage(course, curCourse);
    viewStudentsInCoursePage.mainLoop();
}

#include "ViewStudentsInClassPage.h"

#include "../../../API/GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"
#include "../../../API/OperatorOverload/OperatorOverload.h"
#include "../../TablePage/TablePage.h"

class ViewStudentsInClassPage : public TablePage<Student> {
   private:
    void initColumns() override;
    void initButtons() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewStudentsInClassPage::initColumns() {
    columnTitle =
        new std::string[col]{"No",     "Student ID",    "First Name", "Last Name",
                             "Gender", "Date of Birth", "Social ID"};
    columnWidths = new float[col]{50.0f, 200.0f, 120.0f, 200.0f, 70.0f, 150.0f, 150.0f};
}

void ViewStudentsInClassPage::initButtons() {
    headerButtonTitles[0] = "Add a student";
    headerButtonTitles[1] = "Import CSV of students";
    headerButtonCommands =
        new Command[headerButton]{CREATE_STUDENT, IMPORT_STUDENTS_IN_CLASS};
}

void ViewStudentsInClassPage::convertLinkedListToData() {
    Student* studentsInClassArray;
    createAndSortDataArray(studentsInClassArray);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = studentsInClassArray[i - 1].id;
        tableData[i][2] = studentsInClassArray[i - 1].firstName;
        tableData[i][3] = studentsInClassArray[i - 1].lastName;
        tableData[i][4] = studentsInClassArray[i - 1].gender;
        tableData[i][5] = studentsInClassArray[i - 1].dateOfBirth;
        tableData[i][6] = studentsInClassArray[i - 1].socialID;
    }

    deleteLinkedList(dataLinkedList);
    delete[] studentsInClassArray;
}

void viewStudentsInClassPage(const std::string& className) {
    ViewStudentsInClassPage viewStudentsInClassPage(
        "List of students of class " + className, 7, 0, 2,
        getAllStudentsInClass(className)
    );
    viewStudentsInClassPage.mainLoop();
}

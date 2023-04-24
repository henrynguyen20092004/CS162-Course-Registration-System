#include <algorithm>

#include "../../Function/GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"
#include "../../Function/OperatorOverload/OperatorOverload.h"
#include "../TablePage/TablePage.h"

class ViewStudentsInClassPage : public TablePage {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
};

void ViewStudentsInClassPage::initColumns() {
    columnTitle =
        new std::string[col]{"No",     "Student ID",    "First Name", "Last Name",
                             "Gender", "Date of Birth", "Social ID"};
    columnWidths = new float[col]{50, 200, 120, 330, 80, 180, 150};
}

void ViewStudentsInClassPage::convertLinkedListToData() {
    int arraySize = row - 1;
    Node<Student>* allStudentsInClass = (Node<Student>*)dataLinkedList;
    Student* studentsInClassArray = new Student[arraySize];
    transformLinkedListToArray(allStudentsInClass, studentsInClassArray, arraySize);
    std::sort(studentsInClassArray, studentsInClassArray + arraySize);

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

    deleteLinkedList(allStudentsInClass);
    delete[] studentsInClassArray;
}

void viewStudentsInClassPage(const std::string& className) {
    ViewStudentsInClassPage viewStudentsInClassPage(
        "Student of class " + className, 7, getAllStudentsInClass(className)
    );
    viewStudentsInClassPage.mainLoop();
}

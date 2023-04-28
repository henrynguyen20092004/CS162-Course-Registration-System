#include "ViewClassScoreboardPage.h"

#include <cmath>
#include <cstring>

#include "../../../Function/ConvertScoreToString/ConvertScoreToString.h"
#include "../../../Function/GetAll/GetAllCoursesOfStudentsInClass/GetAllCoursesOfStudentsInClass.h"
#include "../../../Function/GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"
#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../../Struct/Data.h"
#include "../../TablePage/TablePage.h"

class ViewClassScoreboardPage : public TablePage<Student> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    using TablePage::TablePage;
    ViewClassScoreboardPage(
        const std::string& title, const std::string& className, int col,
        Node<Student>* allStudentsInClass, Node<std::string>* allCoursesOfStudentsInClass,
        Node<Score>* allScoresInClass
    );
    std::string className;
    Node<std::string>* allCoursesOfStudentsInClass;
    Node<Score>* allScoresInClass;
};

ViewClassScoreboardPage::ViewClassScoreboardPage(
    const std::string& title, const std::string& className, int col,
    Node<Student>* allStudentsInClass, Node<std::string>* allCoursesOfStudentsInClass,
    Node<Score>* allScoresInClass
)
    : TablePage(title, col, 0, 0, allStudentsInClass),
      className(className),
      allCoursesOfStudentsInClass(allCoursesOfStudentsInClass),
      allScoresInClass(allScoresInClass) {}

void ViewClassScoreboardPage::initColumns() {
    columnTitle = new std::string[col]{"No", "Student ID", "Full Name"};
    Node<std::string>* cur = allCoursesOfStudentsInClass;

    for (int j = 3; j < col - 1; ++j) {
        columnTitle[j] = cur->data;
        cur = cur->next;
    }

    columnTitle[col - 1] = "GPA";
    columnWidths = new float[col]{50.0f, 200.0f, 200.0f};
    columnWidths[col - 1] = 50.0f;

    for (int j = 3; j < col - 1; ++j) {
        columnWidths[j] = 150.0f;
    }
}

void ViewClassScoreboardPage::convertLinkedListToData() {
    Student* allStudentsInClassArray;
    createAndSortDataArray(allStudentsInClassArray);

    int allScoresInClassArraySize = getLinkedListSize(allScoresInClass);
    Score* allScoresInClassArray = new Score[allScoresInClassArraySize];
    transformLinkedListToArray(
        allScoresInClass, allScoresInClassArray, allScoresInClassArraySize
    );
    std::sort(allScoresInClassArray, allScoresInClassArray + allScoresInClassArraySize);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = allStudentsInClassArray[i - 1].id;
        tableData[i][2] = allStudentsInClassArray[i - 1].lastName + " " +
                          allStudentsInClassArray[i - 1].firstName;
    }

    for (int i = 1; i < row; ++i) {
        for (int j = 3; j < col; ++j) {
            tableData[i][j] = "x";
        }

        double gpaComponent = 0;
        int creditSum = 0;

        for (int k = 0; k < allScoresInClassArraySize; ++k) {
            if (allScoresInClassArray[k].studentCourse.studentID == tableData[i][1]) {
                std::string fullCourseName =
                    allScoresInClassArray[k].studentCourse.courseID + "-" +
                    allScoresInClassArray[k].studentCourse.className;

                for (int l = 3; l < col - 1; ++l) {
                    if (tableData[0][l] == fullCourseName) {
                        double result = allScoresInClassArray[k].totalMark;
                        int credit = getCourseCredits(
                            allData.allCourses,
                            allScoresInClassArray[k].studentCourse.courseID,
                            allScoresInClassArray[k].studentCourse.className
                        );
                        creditSum += credit;
                        gpaComponent += result * credit;
                        tableData[i][l] = convertScoreToString(result);
                    }
                }

                double gpa = round(gpaComponent / creditSum * 100.0f) / 100.0f;
                tableData[i][col - 1] = convertScoreToString(gpa);
            }
        }
    }

    deleteLinkedList(dataLinkedList);
    deleteLinkedList(allCoursesOfStudentsInClass);
    deleteLinkedList(allScoresInClass);
}

void viewClassScoreboardPage(const std::string& className) {
    Node<Student>* allStudentsInClass = getAllStudentsInClass(className);
    Node<Score>* allScoresInClass = getAllScoresOfStudentsInClass(allStudentsInClass);
    Node<std::string>* allCoursesOfStudentsInClass =
        getAllCoursesOfStudentsInClass(allScoresInClass);

    ViewClassScoreboardPage viewClassScoreboardPage(
        "The scoreboard of class " + className, className,
        getLinkedListSize(allCoursesOfStudentsInClass) + 4, allStudentsInClass,
        allCoursesOfStudentsInClass, allScoresInClass
    );
    viewClassScoreboardPage.mainLoop();
}

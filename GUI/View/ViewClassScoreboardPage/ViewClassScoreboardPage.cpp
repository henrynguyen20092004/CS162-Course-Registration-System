#include "ViewClassScoreboardPage.h"

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
    std::string className;
    Node<std::string>* allCoursesOfStudentInClass;
    Node<Score>* allScoresInClass;
};

void ViewClassScoreboardPage::initColumns() {
    allScoresInClass = getAllScoresOfStudentsInClass(dataLinkedList);

    allCoursesOfStudentInClass = getAllCoursesOfStudentsInClass(allScoresInClass);
    col = getLinkedListSize(allCoursesOfStudentInClass) + 4;
    columnTitle = new std::string[col]{"No", "Student ID", "Full Name"};
    for (int j = 3; j < col - 1; ++j) {
        columnTitle[j] = allCoursesOfStudentInClass->data;
        allCoursesOfStudentInClass = allCoursesOfStudentInClass->next;
    }
    columnTitle[col - 1] = "GPA";
    columnWidths = new float[col]{50, 200, 120};
    columnWidths[col - 1] = 50;
    for (int j = 3; j < col - 1; ++j) {
        columnWidths[j] = 150;
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
                for (int j = 3; j < col - 1; ++j) {
                    if (tableData[0][j] == fullCourseName) {
                        double result = allScoresInClassArray[k].totalMark;
                        int credit = getCourseCredits(
                            allData.allCourses,
                            allScoresInClassArray[k].studentCourse.courseID,
                            allScoresInClassArray[k].studentCourse.className
                        );
                        creditSum += credit;
                        gpaComponent += result * credit;

                        tableData[i][j] = convertScoreToString(result);
                        // tableData[i][j] = std::to_string(result);
                    }
                }
                double gpa = gpaComponent / creditSum;
                tableData[i][col - 1] = convertScoreToString(gpa);
                // tableData[i][col - 1] = std::to_string(gpa);
            }
        }
    }

    deleteLinkedList(dataLinkedList);
    deleteLinkedList(allScoresInClass);
}

void viewClassScoreboardPage(const std::string& className) {
    ViewClassScoreboardPage viewClassScoreboardPage(
        "The scoreboard of class " + className,
        getLinkedListSize(getAllCoursesOfStudentsInClass(
            getAllScoresOfStudentsInClass(getAllStudentsInClass(className))
        )) + 4,
        getAllStudentsInClass(className)
    );
    viewClassScoreboardPage.className = className;
    viewClassScoreboardPage.mainLoop();
}

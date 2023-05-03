#include "ViewClassScoreboardPage.h"

#include <cmath>

#include "../../../API/CheckAndConvertString/CheckAndConvertString.h"
#include "../../../API/GetAll/GetAllCourses/GetAllCourses.h"
#include "../../../API/GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"
#include "../../../API/OperatorOverload/OperatorOverload.h"
#include "../../TablePage/TablePage.h"

class ViewClassScoreboardPage : public TablePage<Student> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    ViewClassScoreboardPage(
        const std::string& className, int col, Node<Student>* allStudentsInClass,
        Node<std::string>* allCoursesInClassThisSemester, Node<Score>* allScoresOfClass
    );
    std::string className;
    Node<std::string>* allCoursesInClassThisSemester;
    Node<Score>* allScoresOfClass;
};

ViewClassScoreboardPage::ViewClassScoreboardPage(
    const std::string& className, int col, Node<Student>* allStudentsInClass,
    Node<std::string>* allCoursesInClassThisSemester, Node<Score>* allScoresOfClass
)
    : TablePage("Scoreboard of class " + className, col, 0, 0, allStudentsInClass),
      className(className),
      allCoursesInClassThisSemester(allCoursesInClassThisSemester),
      allScoresOfClass(allScoresOfClass) {}

void ViewClassScoreboardPage::initColumns() {
    columnTitle = new std::string[col]{"No", "Student ID", "Full Name"};
    Node<std::string>* cur = allCoursesInClassThisSemester;

    for (int j = 3; j < col - 2; ++j) {
        columnTitle[j] = cur->data;
        cur = cur->next;
    }

    columnTitle[col - 2] = "GPA this semester";
    columnTitle[col - 1] = "Overall GPA";
    columnWidths = new float[col]{50.0f, 200.0f, 200.0f};

    for (int j = 3; j < col; ++j) {
        columnWidths[j] = 180.0f;
    }
}

std::string* findOverallGPAOfClass(
    Node<Score>* allScoresOfClass, Student* studentsInClassArray, int numberOfStudents
) {
    std::string* overallGPA = new std::string[numberOfStudents];

    for (int i = 0; i < numberOfStudents; ++i) {
        double curOverallGPA = 0;
        int creditSum = 0;

        for (Node<Score>* cur = allScoresOfClass; cur; cur = cur->next) {
            if (cur->data.studentCourse.studentID == studentsInClassArray[i].id) {
                int creditNumber = getCourseCredits(cur->data.studentCourse);
                creditSum += creditNumber;
                curOverallGPA += cur->data.totalMark * creditNumber;
            }
        }

        if (creditSum == 0) {
            overallGPA[i] = 'x';
        } else {
            overallGPA[i] = convertScoreToString(curOverallGPA / creditSum);
        }
    }

    return overallGPA;
}

void ViewClassScoreboardPage::convertLinkedListToData() {
    Student* allStudentsInClassArray;
    createAndSortDataArray(allStudentsInClassArray);
    std::string* overallGPA = findOverallGPAOfClass(
        allScoresOfClass, allStudentsInClassArray,
        getLinkedListSize(getAllStudentsInClass(className))
    );

    int allScoresInClassArraySize = getLinkedListSize(allScoresOfClass);
    Score* allScoresInClassArray = new Score[allScoresInClassArraySize];
    transformLinkedListToArray(
        allScoresOfClass, allScoresInClassArray, allScoresInClassArraySize
    );
    std::sort(allScoresInClassArray, allScoresInClassArray + allScoresInClassArraySize);

    for (int j = 0; j < col; ++j) {
        tableData[0][j] = columnTitle[j];
    }

    for (int i = 1; i < row; ++i) {
        tableData[i][0] = std::to_string(i);
        tableData[i][1] = allStudentsInClassArray[i - 1].id;
        tableData[i][2] = allStudentsInClassArray[i - 1].lastName + ' ' +
                          allStudentsInClassArray[i - 1].firstName;
    }

    for (int i = 1; i < row; ++i) {
        for (int j = 3; j < col; ++j) {
            tableData[i][j] = 'x';
        }

        tableData[i][col - 1] = overallGPA[i - 1];
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
                        int credit =
                            getCourseCredits(allScoresInClassArray[k].studentCourse);
                        creditSum += credit;
                        gpaComponent += result * credit;
                        tableData[i][l] = convertScoreToString(result);
                    }
                }

                if (creditSum == 0) {
                    tableData[i][col - 2] = 'x';
                } else {
                    double gpa = round(gpaComponent / creditSum * 100.0f) / 100.0f;
                    tableData[i][col - 2] = convertScoreToString(gpa);
                }
            }
        }
    }

    deleteLinkedList(dataLinkedList);
    deleteLinkedList(allCoursesInClassThisSemester);
    deleteLinkedList(allScoresOfClass);
    delete[] allStudentsInClassArray;
    delete[] allScoresInClassArray;
    delete[] overallGPA;
}

void viewClassScoreboardPage(const std::string& className) {
    Node<Student>* allStudentsInClass = getAllStudentsInClass(className);
    Node<Score>* allScoresOfClass = getAllScoresOfClass(allStudentsInClass);
    Node<std::string>* allCoursesInClassThisSemester =
        getAllCoursesInClassThisSemester(allScoresOfClass);

    ViewClassScoreboardPage viewClassScoreboardPage(
        className, getLinkedListSize(allCoursesInClassThisSemester) + 5,
        allStudentsInClass, allCoursesInClassThisSemester, allScoresOfClass
    );
    viewClassScoreboardPage.mainLoop();
}

#include "ViewClassScoreboardPage.h"

#include <cmath>

#include "../../../Function/CheckAndConvertString/CheckAndConvertString.h"
#include "../../../Function/GetAll/GetAllCourses/GetAllCourses.h"
#include "../../../Function/GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"
#include "../../../Function/OperatorOverload/OperatorOverload.h"
#include "../../TablePage/TablePage.h"

class ViewClassScoreboardPage : public TablePage<Student> {
   private:
    void initColumns() override;
    void convertLinkedListToData() override;

   public:
    ViewClassScoreboardPage(
        const std::string& className, int col, Node<Student>* allStudentsInClass,
        Node<std::string>* allCoursesInClassThisSemester, Node<Score>* allScoresInClass
    );
    std::string className;
    Node<std::string>* allCoursesInClassThisSemester;
    Node<Score>* allScoresInClass;
};

ViewClassScoreboardPage::ViewClassScoreboardPage(
    const std::string& className, int col, Node<Student>* allStudentsInClass,
    Node<std::string>* allCoursesInClassThisSemester, Node<Score>* allScoresInClass
)
    : TablePage("Scoreboard of class " + className, col, 0, 0, allStudentsInClass),
      className(className),
      allCoursesInClassThisSemester(allCoursesInClassThisSemester),
      allScoresInClass(allScoresInClass) {}

void ViewClassScoreboardPage::initColumns() {
    columnTitle = new std::string[col]{"No", "Student ID", "Full Name"};
    Node<std::string>* cur = allCoursesInClassThisSemester;

    for (int j = 3; j < col - 2; ++j) {
        columnTitle[j] = cur->data;
        cur = cur->next;
    }

    columnTitle[col - 2] = "GPA this Semester";
    columnTitle[col - 1] = "Overall GPA";
    columnWidths = new float[col]{50.0f, 200.0f, 200.0f};

    for (int j = 3; j < col; ++j) {
        columnWidths[j] = 180.0f;
    }
}

double* findOverallGPAOfClass(
    Node<Score>* allScoresInClass, Node<Course>* allCourses,
    Student* studentsInClassArray, int numberOfStudents
) {
    double* overallGPA = new double[numberOfStudents];
    for (int i = 0; i < numberOfStudents; ++i) {
        overallGPA[i] = 0;
    }

    for (int i = 0; i < numberOfStudents; ++i) {
        int creditSum = 0;
        for (Node<Score>* cur = allScoresInClass; cur; cur = cur->next) {
            if (cur->data.studentCourse.studentID == studentsInClassArray[i].id) {
                int creditNumber = getCourseCredits(
                    allCourses, cur->data.studentCourse.courseID,
                    cur->data.studentCourse.className
                );
                creditSum += creditNumber;
                overallGPA[i] += cur->data.totalMark * creditNumber;
            }
        }
        overallGPA[i] /= creditSum;
    }
    return overallGPA;
}

void ViewClassScoreboardPage::convertLinkedListToData() {
    Student* allStudentsInClassArray;
    createAndSortDataArray(allStudentsInClassArray);
    double* overallGPA = nullptr;
    overallGPA = findOverallGPAOfClass(
        allScoresInClass, getAllCourses(), allStudentsInClassArray,
        getLinkedListSize(getAllStudentsInClass(className))
    );

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
        tableData[i][col - 1] = convertScoreToString(overallGPA[i - 1]);

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
                            GlobalVar::allData.allCourses,
                            allScoresInClassArray[k].studentCourse.courseID,
                            allScoresInClassArray[k].studentCourse.className
                        );
                        creditSum += credit;
                        gpaComponent += result * credit;
                        tableData[i][l] = convertScoreToString(result);
                    }
                }

                double gpa = round(gpaComponent / creditSum * 100.0f) / 100.0f;
                tableData[i][col - 2] = convertScoreToString(gpa);
            }
        }
    }

    deleteLinkedList(dataLinkedList);
    deleteLinkedList(allCoursesInClassThisSemester);
    deleteLinkedList(allScoresInClass);
    delete[] allStudentsInClassArray;
    delete[] allScoresInClassArray;
    delete[] overallGPA;
}

void viewClassScoreboardPage(const std::string& className) {
    Node<Student>* allStudentsInClass = getAllStudentsInClass(className);
    Node<Score>* allScoresInClass = getAllScoresOfStudentsInClass(allStudentsInClass);
    Node<std::string>* allCoursesInClassThisSemester =
        getAllCoursesInClassThisSemester(GlobalVar::currentSemester, allScoresInClass);

    ViewClassScoreboardPage viewClassScoreboardPage(
        className, getLinkedListSize(allCoursesInClassThisSemester) + 5,
        allStudentsInClass, allCoursesInClassThisSemester, allScoresInClass
    );
    viewClassScoreboardPage.mainLoop();
}

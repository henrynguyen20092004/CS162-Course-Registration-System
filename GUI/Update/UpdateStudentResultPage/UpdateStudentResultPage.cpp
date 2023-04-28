#include "UpdateStudentResultPage.h"

#include <cstring>

#include "../../../Function/ConvertScoreToString/ConvertScoreToString.h"
#include "../../../Function/GetAll/GetAllScores/GetAllScores.h"
#include "../../../Function/GetAll/GetAllStudentsInCourse/GetAllStudentsInCourse.h"
#include "../../../Function/SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"
#include "../../../Function/Update/UpdateStudentResult/UpdateStudentResult.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class UpdateStudentResultPage : public FormPage {
   private:
    Course course;
    Score score;
    char *previousCourseDropDownItem, *previousStudentIDDropDownItem;
    void initInputs() override;
    void drawInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
    UpdateStudentResultPage();
    ~UpdateStudentResultPage();
};

UpdateStudentResultPage::UpdateStudentResultPage()
    : FormPage(
          "Update student's result", 4, 2, 2,
          {SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.75f}, VIEW_SCOREBOARD_OF_COURSE
      ) {
    previousCourseDropDownItem = new char[MAX_INPUT_CHAR];
    previousCourseDropDownItem[0] = '\0';
    previousStudentIDDropDownItem = new char[MAX_INPUT_CHAR];
    previousStudentIDDropDownItem[0] = '\0';
}

void UpdateStudentResultPage::initInputs() {
    dropDowns[0] = DropDown("Course", allData.allCourses, inputPos[0], inputWidth);
    textInputs[0] = TextInput("Other mark", inputs[0], inputPos[2], inputWidth);
    textInputs[1] = TextInput("Midterm mark", inputs[1], inputPos[3], inputWidth);
    textInputs[2] = TextInput("Final mark", inputs[2], inputPos[4], inputWidth);
    textInputs[3] = TextInput("Total mark", inputs[3], inputPos[5], inputWidth);
}

void UpdateStudentResultPage::drawInputs() {
    if (strcmp(dropDownItems[0], previousCourseDropDownItem)) {
        std::string *courseIDAndClassName = new std::string[2];
        splitCourseToIDAndClassName(courseIDAndClassName, dropDownItems[0]);
        course.id = courseIDAndClassName[0];
        course.className = courseIDAndClassName[1];
        delete[] courseIDAndClassName;
        Node<Student> *allStudentsInCourse = getAllStudentsInCourse(course);
        dropDowns[1] =
            DropDown("Student ID", allStudentsInCourse, inputPos[1], inputWidth);
        deleteLinkedList(allStudentsInCourse);
        strcpy(previousCourseDropDownItem, dropDownItems[0]);
        score.otherMark = INT_MIN;
        dropDownItems[1][0] = '\0';
        inputs[0][0] = '\0';
    }

    if (dropDownItems[1][0] != '\0' &&
        strcmp(dropDownItems[1], previousStudentIDDropDownItem)) {
        for (Node<Score> *cur = allData.allScores; cur; cur = cur->next) {
            StudentCourse studentCourse = cur->data.studentCourse;
            if (!strcmp(studentCourse.studentID.c_str(), dropDownItems[1]) &&
                studentCourse.courseID == course.id &&
                studentCourse.className == course.className) {
                score = cur->data;
                break;
            }
        }

        if (score.otherMark != INT_MIN) {
            strcpy(inputs[0], convertScoreToString(score.otherMark).c_str());
            strcpy(inputs[1], convertScoreToString(score.midtermMark).c_str());
            strcpy(inputs[2], convertScoreToString(score.finalMark).c_str());
            strcpy(inputs[3], convertScoreToString(score.totalMark).c_str());
        } else {
            inputs[0][0] = '\0';
        }

        strcpy(previousStudentIDDropDownItem, dropDownItems[1]);
    }

    if (dropDownItems[1][0] != '\0' && score.otherMark != INT_MIN) {
        for (int i = 0; i < 4; ++i) {
            if (textInputs[i].drawTextInput(scroll.y)) {
                submit();
            }
        }
    }

    if (dropDownItems[0][0] != '\0') {
        dropDowns[1].drawDropDown(dropDownItems[1], scroll.y);
    }

    dropDowns[0].drawDropDown(dropDownItems[0], scroll.y);
}

void UpdateStudentResultPage::submitCallBack() {
    updateStudentResult(inputs, dropDownItems, score);
}

void updateStudentResultPage() {
    UpdateStudentResultPage updateStudentResultPage;
    updateStudentResultPage.mainLoop();
}

UpdateStudentResultPage::~UpdateStudentResultPage() {
    delete[] previousCourseDropDownItem;
    delete[] previousStudentIDDropDownItem;
}

#include "UpdateCoursePage.h"

#include <cstring>

#include "../../../Function/SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"
#include "../../../Function/Update/UpdateCourse/UpdateCourse.h"
#include "../../../GlobalVar/GlobalVar.h"
#include "../../FormPage/FormPage.h"

class UpdateCoursePage : public FormPage {
   private:
    char *previousCourseDropDownItem;
    void initInputs() override;
    void drawInputs() override;
    void submitCallBack() override;

   public:
    UpdateCoursePage();
    ~UpdateCoursePage();
};

UpdateCoursePage::UpdateCoursePage()
    : FormPage(
          "Update course information", 4, 3, 2,
          {SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.35f}
      ) {
    previousCourseDropDownItem = new char[MAX_INPUT_CHAR];
    previousCourseDropDownItem[0] = '\0';
}

int dayOfWeekToIndex(const std::string &dayOfWeek) {
    switch (dayOfWeek[0]) {
        case 'M':
            return 0;
        case 'T':
            switch (dayOfWeek[1]) {
                case 'U':
                    return 1;
                default:
                    return 3;
            }
        case 'W':
            return 2;
        case 'F':
            return 4;
        default:
            return 5;
    }
}

void UpdateCoursePage::initInputs() {
    dropDowns[0] =
        DropDown("Course", GlobalVar::allData.allCourses, inputPos[0], inputWidth);
    textInputs[0] = TextInput("Course name", inputs[0], inputPos[1], inputWidth);
    textInputs[1] = TextInput("Teacher name", inputs[1], inputPos[2], inputWidth);
    textInputs[2] = TextInput("Credits", inputs[2], inputPos[3], inputWidth);
    textInputs[3] =
        TextInput("Maximum number of students", inputs[3], inputPos[4], inputWidth);
    dropDowns[1] =
        DropDown("Day of week", "MON;TUE;WED;THU;FRI;SAT", inputPos[5], inputWidth);
    dropDowns[2] = DropDown("Session number", "1;2;3;4", inputPos[6], inputWidth);
}

void UpdateCoursePage::drawInputs() {
    if (strcmp(dropDownItems[0], previousCourseDropDownItem)) {
        std::string *courseIDAndClassName = new std::string[2];
        splitCourseToIDAndClassName(courseIDAndClassName, dropDownItems[0]);

        for (Node<Course> *cur = GlobalVar::allData.allCourses; cur; cur = cur->next) {
            Course course = cur->data;
            if (course.id == courseIDAndClassName[0] &&
                course.className == courseIDAndClassName[1]) {
                strcpy(inputs[0], course.name.c_str());
                strcpy(inputs[1], course.teacherName.c_str());
                strcpy(inputs[2], std::to_string(course.credits).c_str());
                strcpy(inputs[3], std::to_string(course.maxStudent).c_str());
                strcpy(dropDownItems[1], course.dayOfWeek.c_str());
                strcpy(dropDownItems[2], std::to_string(course.sessionNumber).c_str());
                dropDowns[1].activeItemIndex = dayOfWeekToIndex(course.dayOfWeek);
                dropDowns[2].activeItemIndex =
                    stoi(std::to_string(course.sessionNumber)) - 1;
                break;
            }
        }

        delete[] courseIDAndClassName;
        strcpy(previousCourseDropDownItem, dropDownItems[0]);
    }

    if (dropDownItems[0][0] != '\0') {
        for (int i = 0; i < 4; ++i) {
            if (textInputs[i].drawTextInput(scroll.y)) {
                submit();
            }
        }

        for (int i = 2; i > 0; --i) {
            dropDowns[i].drawDropDown(dropDownItems[i], scroll.y);
        }
    }

    dropDowns[0].drawDropDown(dropDownItems[0], scroll.y);
}

void UpdateCoursePage::submitCallBack() {
    updateCourse(inputs, dropDownItems);
    successText = "Course successfully updated!";
}

void updateCoursePage() {
    UpdateCoursePage updateCoursePage;
    updateCoursePage.mainLoop();
}

UpdateCoursePage::~UpdateCoursePage() { delete[] previousCourseDropDownItem; }

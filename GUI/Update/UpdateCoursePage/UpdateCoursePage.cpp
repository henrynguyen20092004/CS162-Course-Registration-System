#include "UpdateCoursePage.h"

#include "../../../Function/Update/UpdateCourse/UpdateCourse.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class UpdateCoursePage : public FormPage {
   private:
    void initComponents() override;
    void drawFormInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void UpdateCoursePage::initComponents() {
    FormPage::initComponents();
    dropDowns[0] = DropDown(allData.allCourses, inputPos[0], inputWidth);
    textInputs[0] = TextInput(inputs[0], inputPos[1], inputWidth);
    textInputs[1] = TextInput(inputs[1], inputPos[2], inputWidth);
    textInputs[2] = TextInput(inputs[2], inputPos[3], inputWidth);
    textInputs[3] = TextInput(inputs[3], inputPos[4], inputWidth);
    dropDowns[1] = DropDown("MON;TUE;WED;THU;FRI;SAT", inputPos[5], inputWidth);
    dropDowns[2] = DropDown("1;2;3;4", inputPos[6], inputWidth);
}

void UpdateCoursePage::drawFormInputs() {
    if (textInputs[0].drawTextInput("Course name") ||
        textInputs[1].drawTextInput("Teacher name") ||
        textInputs[2].drawTextInput("Credits") ||
        textInputs[3].drawTextInput("Maximum number of students")) {
        submit();
    }

    dropDowns[2].drawDropDown("Session number", dropDownItems[2]);
    dropDowns[1].drawDropDown("Day of week", dropDownItems[1]);
    dropDowns[0].drawDropDown("Course", dropDownItems[0]);
}

void UpdateCoursePage::submitCallBack() { updateCourse(inputs, dropDownItems); }

void updateCoursePage() {
    UpdateCoursePage updateCoursePage(
        "Update Course Information", 4, 3, 2,
        {SCREEN_WIDTH / 1.6f, SCREEN_HEIGHT / 1.35f}, "Submit"
    );
    updateCoursePage.mainLoop();
}

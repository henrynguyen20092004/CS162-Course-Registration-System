#include "CreateCoursePage.h"

#include "../../../Function/Create/CreateCourse/CreateCourse.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class CreateCoursePage : public FormPage {
   private:
    void initComponents() override;
    void drawFormInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateCoursePage::initComponents() {
    FormPage::initComponents();
    textInputs[0] = TextInput(inputs[0], inputPos[0], inputWidth);
    textInputs[1] = TextInput(inputs[1], inputPos[1], inputWidth);
    textInputs[2] = TextInput(inputs[2], inputPos[2], inputWidth);
    textInputs[3] = TextInput(inputs[3], inputPos[3], inputWidth);
    textInputs[4] = TextInput(inputs[4], inputPos[4], inputWidth);
    textInputs[5] = TextInput(inputs[5], inputPos[5], inputWidth);
    dropDowns[0] = DropDown("MON;TUE;WED;THU;FRI;SAT", inputPos[6], inputWidth);
    dropDowns[1] = DropDown("1;2;3;4", inputPos[7], inputWidth);
}

void CreateCoursePage::drawFormInputs() {
    if (textInputs[0].drawTextInput("Course ID") ||
        textInputs[1].drawTextInput("Class Name") ||
        textInputs[2].drawTextInput("Course Name") ||
        textInputs[3].drawTextInput("Teacher Name") ||
        textInputs[4].drawTextInput("Number of credit") ||
        textInputs[5].drawTextInput("Maximum number of student")) {
        submit();
    }

    dropDowns[1].drawDropDown("Session number", dropDownItems[1]);
    dropDowns[0].drawDropDown("Day of week", dropDownItems[0]);
}

void CreateCoursePage::submitCallBack() {
    createCourse(currentSemester, inputs, dropDownItems);
}

void createCoursePage() {
    CreateCoursePage createCoursePage(
        "Add course to semester", 6, 2, 2, {SCREEN_WIDTH / 1.6f, SCREEN_HEIGHT / 1.35f}
    );
    createCoursePage.mainLoop();
}

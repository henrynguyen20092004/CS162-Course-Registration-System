#include "AddStudentToCoursePage.h"

#include "../../Function/AddStudentToCourse/AddStudentToCourse.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"

class AddStudentToCoursePage : public FormPage {
   private:
    void initComponents() override;
    void drawFormInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void AddStudentToCoursePage::initComponents() {
    FormPage::initComponents();
    dropDowns[0] = DropDown(allData.allCourses, inputPos[0], inputWidth);
    textInputs[0] = TextInput(inputs[0], inputPos[1], inputWidth);
}

void AddStudentToCoursePage::drawFormInputs() {
    if (textInputs[0].drawTextInput("Student ID")) {
        submit();
    }

    dropDowns[0].drawDropDown("Course name", dropDownItems[0]);
}

void AddStudentToCoursePage::submitCallBack() {
    addStudentToCourse(inputs, dropDownItems);
}

void addStudentToCoursePage() {
    AddStudentToCoursePage addStudentToCoursePage(
        "Add student to course", 1, 1, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f}
    );
    addStudentToCoursePage.mainLoop();
}

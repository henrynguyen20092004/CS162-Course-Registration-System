#include "AddStudentToCoursePage.h"

#include "../../Function/AddStudentToCourse/AddStudentToCourse.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class AddStudentToCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void AddStudentToCoursePage::drawFormInput() {
    TextInput courseIDInput(inputs[0], inputPos[0], inputWidth);
    TextInput classNameInput(inputs[1], inputPos[1], inputWidth);
    TextInput studentIDInput(inputs[2], inputPos[2], inputWidth);

    if (courseIDInput.drawTextInput("Course ID", editModes[0]) ||
        classNameInput.drawTextInput("Class Name", editModes[1]) ||
        studentIDInput.drawTextInput("Student ID", editModes[2])) {
        submitCallBack();
    }
}

void AddStudentToCoursePage::submitCallBack() {
    try {
        addStudentToCourse(inputs[0], inputs[1], inputs[2]);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void addStudentToCoursePage() {
    AddStudentToCoursePage addStudentToCoursePage(
        "Add student to course", 3, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 1.7f}
    );
    addStudentToCoursePage.mainLoop();
}

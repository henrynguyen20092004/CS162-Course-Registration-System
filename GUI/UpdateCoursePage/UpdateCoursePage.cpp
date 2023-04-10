#include "UpdateCoursePage.h"

#include <cstring>

#include "../../Function/Update/UpdateCourse/UpdateCourse.h"
#include "../../Struct/Data.h"
#include "../Button/Button.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../HidePassword/HidePassword.h"
#include "../TextInput/TextInput.h"

class UpdateCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void UpdateCoursePage::drawFormInput() {
    TextInput courseIDInput(inputs[0], inputPos[0], inputWidth);
    TextInput classNameInput(inputs[1], inputPos[1], inputWidth);
    TextInput courseNameInput(inputs[2], inputPos[2], inputWidth);
    TextInput teacherNameInput(inputs[3], inputPos[3], inputWidth);
    TextInput creditsInput(inputs[4], inputPos[4], inputWidth);
    TextInput maxStudentInput(inputs[5], inputPos[5], inputWidth);
    TextInput dayOfWeekInput(inputs[6], inputPos[6], inputWidth);
    TextInput sessionNumberInput(inputs[7], inputPos[7], inputWidth);

    if (courseIDInput.drawTextInput("Course ID", editModes[0]) ||
        classNameInput.drawTextInput("Class name", editModes[1]) ||
        courseNameInput.drawTextInput("Course name", editModes[2]) ||
        teacherNameInput.drawTextInput("Teacher name", editModes[3]) ||
        creditsInput.drawTextInput("Credits", editModes[4]) ||
        maxStudentInput.drawTextInput("Maximum number of students", editModes[5]) ||
        dayOfWeekInput.drawTextInput("Day of week", editModes[6]) ||
        sessionNumberInput.drawTextInput("Session number", editModes[7])) {
        submitCallBack();
    }
}

void UpdateCoursePage::submitCallBack() {
    try {
        updateCourse(inputs);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void updateCoursePage() {
    UpdateCoursePage updateCoursePage(
        "Update Course Information", 8, 2, {SCREEN_WIDTH / 1.4f, SCREEN_HEIGHT / 1.4f},
        "Submit"
    );

    updateCoursePage.mainLoop();
}

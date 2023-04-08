#include "UpdateCoursePage.h"

#include <cstring>

#include "../../Function/Update/UpdateCourse/UpdateCourse.h"
#include "../../Struct/Data.h"
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
    using Page::mainLoop;
    User currentUser;
};

void UpdateCoursePage::drawFormInput() {
    TextInput courseIDInput(inputs[0], inputPosY[0] + 50, 250);
    TextInput classNameInput(inputs[1], inputPosY[1] + 50, 250);
    TextInput courseNameInput(inputs[2], inputPosY[2] + 50, 250);
    TextInput teacherNameInput(inputs[3], inputPosY[3] + 50, 250);
    TextInput creditsInput(inputs[4], inputPosY[0] + 50, 800);
    TextInput maxStudentInput(inputs[5], inputPosY[1] + 50, 800);
    TextInput dayOfWeekInput(inputs[6], inputPosY[2] + 50, 800);
    TextInput sessionNumberInput(inputs[7], inputPosY[3] + 50, 800);

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
        std::cout << "Successful!";
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void updateCoursePage() {
    UpdateCoursePage updateCoursePage(
        "Update Course Information", 8, 200.0f,
        {SCREEN_WIDTH / 1.3f, SCREEN_HEIGHT / 1.3f}, "Submit"
    );

    updateCoursePage.mainLoop();
}

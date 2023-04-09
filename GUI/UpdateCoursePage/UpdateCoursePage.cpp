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
    void drawReturnButton() override;

   public:
    using FormPage::FormPage;
    using Page::mainLoop;
};

void UpdateCoursePage::drawReturnButton() {
    Button returnButton("Return", 150, 1250, 100);

    if (returnButton.drawButton()) {
        stopLoop = true;
    }
}

void UpdateCoursePage::drawFormInput() {
    TextInput courseIDInput(inputs[0], inputPosY[0], 285);
    TextInput classNameInput(inputs[1], inputPosY[1], 285);
    TextInput courseNameInput(inputs[2], inputPosY[2], 285);
    TextInput teacherNameInput(inputs[3], inputPosY[3], 285);
    TextInput creditsInput(inputs[4], inputPosY[0], 855);
    TextInput maxStudentInput(inputs[5], inputPosY[1], 855);
    TextInput dayOfWeekInput(inputs[6], inputPosY[2], 855);
    TextInput sessionNumberInput(inputs[7], inputPosY[3], 855);

    drawReturnButton();

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
        std::cout << "Successful!";
        throw std::invalid_argument("Course successfully updated!");
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void updateCoursePage() {
    UpdateCoursePage updateCoursePage(
        "Update Course Information", 8, 250.f,
        {SCREEN_WIDTH / 1.4f, SCREEN_HEIGHT / 1.4f}, "Submit"
    );

    updateCoursePage.mainLoop();
}

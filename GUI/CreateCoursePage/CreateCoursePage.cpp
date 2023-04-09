#include "CreateCoursePage.h"

#include "../../Function/Create/CreateCourse/CreateCourse.h"
#include "../../Function/CurrentSemester/CurrentSemester.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class CreateCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
    using Page::mainLoop;
};

void CreateCoursePage ::drawFormInput() {
    TextInput courseIDIput(inputs[0], inputPosY[0], 285);
    TextInput classNameInput(inputs[1], inputPosY[1], 285);
    TextInput courseNameInput(inputs[2], inputPosY[2], 285);
    TextInput teacherNameInput(inputs[3], inputPosY[3], 285);
    TextInput creditsInput(inputs[4], inputPosY[0], 885);
    TextInput maxStudentInput(inputs[5], inputPosY[1], 885);
    TextInput dayOfWeekInput(inputs[6], inputPosY[2], 885);
    TextInput sessionNumberInput(inputs[7], inputPosY[3], 885);

    if (courseIDIput.drawTextInput("Course ID", editModes[0]) ||
            classNameInput.drawTextInput("Class Name", editModes[1]) ||
            courseNameInput.drawTextInput("Course Name", editModes[2]) ||
            teacherNameInput.drawTextInput("Teacher Name", editModes[3]) ||
            creditsInput.drawTextInput("Number of credit(s)", editModes[4]) ||
            maxStudentInput.drawTextInput("Maximum number of student", editModes[5]),
        dayOfWeekInput.drawTextInput(
            "Day of week that course will be perfomed", editModes[6]
        ),
        sessionNumberInput.drawTextInput(
            "Session number that course will be perfomed", editModes[7]
        )) {
        submitCallBack();
    }
}

void CreateCoursePage::submitCallBack() {
    Semester curSemester = getCurrentSemester();

    try {
        createCourse(
            curSemester, inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5],
            inputs[6], inputs[7]
        );
    } catch (std::exception &error) {
        errorText = error.what();
    }
}
void createCoursePage() {
    CreateCoursePage createCoursePage(
        "Add course to semester", 8, 250.0f, {SCREEN_WIDTH / 1.4f, SCREEN_HEIGHT / 1.4f}
    );
    createCoursePage.mainLoop();
}

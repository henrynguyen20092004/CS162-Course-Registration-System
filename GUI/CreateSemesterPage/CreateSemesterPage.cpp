#include "CreateSemesterPage.h"

#include "../../Function/Check/CheckSemester/CheckSemester.h"
#include "../../Function/Create/CreateSemester/CreateSemester.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class CreateSemesterPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
    using Page::mainLoop;
    Semester curSemester;
};

void CreateSemesterPage ::drawFormInput() {
    TextInput schoolYearInput(inputs[0], inputPosY[0]);
    TextInput semesterNumberInput(inputs[1], inputPosY[1]);
    TextInput startDateInput(inputs[2], inputPosY[2]);
    TextInput endDateInput(inputs[3], inputPosY[3]);

    if (schoolYearInput.drawTextInput("School Year", editModes[0]) ||
        semesterNumberInput.drawTextInput("Semester Number", editModes[1]) ||
        startDateInput.drawTextInput("Start Date", editModes[2]) ||
        endDateInput.drawTextInput("End Date", editModes[3])) {
        submitCallBack();
    }
}

void CreateSemesterPage ::submitCallBack() {
    try {
        curSemester = createSemester(inputs[0], inputs[1], inputs[2], inputs[3]);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

Semester createSemesterPage() {
    CreateSemesterPage createSemesterPage(
        "Create semester", 4, 250.0f, {SCREEN_WIDTH / 2.9f, SCREEN_HEIGHT / 1.35f}
    );
    createSemesterPage.mainLoop();
    return createSemesterPage.curSemester;
}
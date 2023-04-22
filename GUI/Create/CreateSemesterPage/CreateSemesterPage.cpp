#include "CreateSemesterPage.h"

#include "../../../Function/Create/CreateSemester/CreateSemester.h"
#include "../../../Struct/Data.h"
#include "../../DropDown/Dropdown.h"
#include "../../FormPage/FormPage.h"
#include "../../TextInput/TextInput.h"

class CreateSemesterPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateSemesterPage::drawFormInput() {
    DropDown schoolYearDropDown(allData.allSchoolYears, inputPos[0], inputWidth);
    DropDown semesterNumberDropDown("1;2;3", inputPos[1], inputWidth);
    TextInput startDateInput(inputs[0], inputPos[2], inputWidth);
    TextInput endDateInput(inputs[1], inputPos[3], inputWidth);

    if (startDateInput.drawTextInput("Start date", textInputEditModes[0]) ||
        endDateInput.drawTextInput("End date", textInputEditModes[1])) {
        submit();
    }

    semesterNumberDropDown.drawDropDown(
        "Semester number", dropDownItems[1], dropDownActiveItems[1], dropDownEditModes[1]
    );
    schoolYearDropDown.drawDropDown(
        "School year", dropDownItems[0], dropDownActiveItems[0], dropDownEditModes[0]
    );
}

void CreateSemesterPage::submitCallBack() {
    currentSemester = createSemester(inputs, dropDownItems);
}

void createSemesterPage() {
    CreateSemesterPage createSemesterPage(
        "Create semester", 2, 2, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 1.35f}
    );
    createSemesterPage.mainLoop();
}

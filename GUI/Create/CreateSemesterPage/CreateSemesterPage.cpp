#include "CreateSemesterPage.h"

#include "../../../Function/Create/CreateSemester/CreateSemester.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class CreateSemesterPage : public FormPage {
   private:
    void initComponents() override;
    void drawFormInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateSemesterPage::initComponents() {
    FormPage::initComponents();
    dropDowns[0] = DropDown(allData.allSchoolYears, inputPos[0], inputWidth);
    dropDowns[1] = DropDown("1;2;3", inputPos[1], inputWidth);
    textInputs[0] = TextInput(inputs[0], inputPos[2], inputWidth);
    textInputs[1] = TextInput(inputs[1], inputPos[3], inputWidth);
}

void CreateSemesterPage::drawFormInputs() {
    if (textInputs[0].drawTextInput("Start date (dd/mm/yyyy)") ||
        textInputs[1].drawTextInput("End date (dd/mm/yyyy)")) {
        submit();
    }

    dropDowns[1].drawDropDown("Semester number", dropDownItems[1]);
    dropDowns[0].drawDropDown("School year (yyyy-yyyy)", dropDownItems[0]);
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

#include "CreateSemesterPage.h"

#include "../../../Function/Create/CreateSemester/CreateSemester.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class CreateSemesterPage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateSemesterPage::initInputs() {
    dropDowns[0] =
        DropDown("School year", allData.allSchoolYears, inputPos[0], inputWidth);
    dropDowns[1] = DropDown("Semester number", "1;2;3", inputPos[1], inputWidth);
    textInputs[0] =
        TextInput("Start date (dd/mm/yyyy)", inputs[0], inputPos[2], inputWidth);
    textInputs[1] =
        TextInput("End date (dd/mm/yyyy)", inputs[1], inputPos[3], inputWidth);
}

void CreateSemesterPage::submitCallBack() {
    currentSemester = createSemester(inputs, dropDownItems);
}

void createSemesterPage() {
    CreateSemesterPage createSemesterPage(
        "Create semester", 2, 2, 1, {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.35f}
    );
    createSemesterPage.mainLoop();
}

#include "ChangeCurrentSemesterPage.h"

#include "../../Function/ChangeCurrentSemester/ChangeCurrentSemester.h"
#include "../../GlobalVar/GlobalVar.h"
#include "../FormPage/FormPage.h"

class ChangeCurrentSemesterPage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ChangeCurrentSemesterPage::initInputs() {
    dropDowns[0] = DropDown(
        "School year", GlobalVar::allData.allSchoolYears, inputPos[0], inputWidth
    );
    dropDowns[1] = DropDown("Semester number", "1;2;3", inputPos[1], inputWidth);
}

void ChangeCurrentSemesterPage::submitCallBack() {
    GlobalVar::currentSemester = changeCurrentSemester(dropDownItems);
    GlobalVar::currentCommand = GlobalVar::previousCommand;
    stopLoop = true;
}

void changeCurrentSemesterPage() {
    ChangeCurrentSemesterPage changeCurrentSemesterPage(
        "Change the current semester", 0, 2, 1,
        {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.75f}
    );
    changeCurrentSemesterPage.mainLoop();
}

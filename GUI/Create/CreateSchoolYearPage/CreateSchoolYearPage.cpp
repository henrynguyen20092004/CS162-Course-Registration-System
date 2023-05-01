#include "CreateSchoolYearPage.h"

#include "../../../Function/Create/CreateSchoolYear/CreateSchoolYear.h"
#include "../../../GlobalVar/GlobalVar.h"
#include "../../FormPage/FormPage.h"

class CreateSchoolYearPage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateSchoolYearPage::initInputs() {
    textInputs[0] =
        TextInput("School year (yyyy-yyyy)", inputs[0], inputPos[0], inputWidth);
}

void CreateSchoolYearPage::submitCallBack() {
    createSchoolYear(inputs[0]);
    successText = "School year successfully created!";
}

void createSchoolYearPage() {
    CreateSchoolYearPage createSchoolYearPage(
        "Create a school year", 1, 0, 1, {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 3.0f}
    );
    createSchoolYearPage.mainLoop();
}

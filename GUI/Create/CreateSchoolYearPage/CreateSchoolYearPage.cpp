#include "CreateSchoolYearPage.h"

#include "../../../Function/Create/CreateSchoolYear/CreateSchoolYear.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class CreateSchoolYearPage : public FormPage {
   private:
    void initComponents() override;
    void drawFormInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateSchoolYearPage::initComponents() {
    FormPage::initComponents();
    textInputs[0] = TextInput(inputs[0], inputPos[0], inputWidth);
}

void CreateSchoolYearPage::drawFormInputs() {
    if (textInputs[0].drawTextInput("School year (yyyy-yyyy)")) {
        submit();
    }
}

void CreateSchoolYearPage::submitCallBack() { createSchoolYear(inputs[0]); }

void createSchoolYearPage() {
    CreateSchoolYearPage createSchoolYearPage(
        "Create a school year", 1, 0, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 3.0f}
    );
    createSchoolYearPage.mainLoop();
}

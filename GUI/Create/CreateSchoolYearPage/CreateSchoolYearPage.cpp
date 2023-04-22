#include "CreateSchoolYearPage.h"

#include "../../../Function/Create/CreateSchoolYear/CreateSchoolYear.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"
#include "../../TextInput/TextInput.h"

class CreateSchoolYearPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateSchoolYearPage::drawFormInput() {
    TextInput schoolYearInput(inputs[0], inputPos[0], inputWidth);

    if (schoolYearInput.drawTextInput("School year (yyyy-yyyy)", textInputEditModes[0])) {
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

#include "CreateSchoolYearPage.h"

#include "../../Function/Create/CreateSchoolYear/CreateSchoolYear.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class CreateSchoolYearPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
    using Page::mainLoop;
};

void CreateSchoolYearPage::drawFormInput() {
    TextInput schoolYearInput(inputs[0], inputPos[0], inputWidth);

    if (schoolYearInput.drawTextInput(
            "Please enter the school year (yyyy-yyyy)", editModes[0]
        )) {
        submitCallBack();
    }
}

void CreateSchoolYearPage::submitCallBack() {
    try {
        createSchoolYear(inputs[0]);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void createSchoolYearPage() {
    CreateSchoolYearPage createSchoolYearPage(
        "Create a school year", 1, 1, {SCREEN_WIDTH / 3.1f, SCREEN_HEIGHT / 3.1f},
        "Submit"
    );
    createSchoolYearPage.mainLoop();
}

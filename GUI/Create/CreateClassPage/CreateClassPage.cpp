#include "CreateClassPage.h"

#include "../../../Function/Create/CreateClass/CreateClass.h"
#include "../../FormPage/FormPage.h"
#include "../../TextInput/TextInput.h"

class CreateClassPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateClassPage::drawFormInput() {
    TextInput classNameInput(inputs[0], inputPos[0], inputWidth);

    if (classNameInput.drawTextInput("Class name", textInputEditModes[0])) {
        submitCallBack();
    }
}

void CreateClassPage::submitCallBack() {
    try {
        createClass(inputs[0]);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void createClassPage() {
    CreateClassPage createClassPage(
        "Create a class", 1, 0, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 3.0f}
    );
    createClassPage.mainLoop();
}

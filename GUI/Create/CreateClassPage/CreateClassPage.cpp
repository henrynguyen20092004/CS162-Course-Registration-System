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

    if (classNameInput.drawTextInput("New class name", editModes[0])) {
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
        "Create new class", 1, 1, 422.f, {SCREEN_WIDTH / 3.1f, SCREEN_HEIGHT / 3.1f}
    );
    createClassPage.mainLoop();
}

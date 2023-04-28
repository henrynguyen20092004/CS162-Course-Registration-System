#include "ChangePasswordPage.h"

#include "../../Function/ChangePassword/ChangePassword.h"
#include "../FormPage/FormPage.h"
#include "../HidePassword/HidePassword.h"

class ChangePasswordPage : public FormPage {
   private:
    void initInputs() override;
    void drawInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ChangePasswordPage::initInputs() {
    textInputs[0] = TextInput("Old password", inputs[0], inputPos[0], inputWidth);
    textInputs[1] = TextInput("New password", inputs[1], inputPos[1], inputWidth);
    textInputs[2] = TextInput("Confirm new password", inputs[2], inputPos[2], inputWidth);
}

void ChangePasswordPage::drawInputs() {
    for (int i = 0; i < 3; ++i) {
        hidePassword(inputs[i], inputs[i + 3]);
    }

    for (int i = 0; i < numberOfTextInputs; ++i) {
        if (textInputs[i].drawTextInput(scroll.y)) {
            submit();
        }
    }
}

void ChangePasswordPage::submitCallBack() { changePassword(currentUser, inputs); }

void changePasswordPage() {
    ChangePasswordPage changePasswordPage(
        "Change your password", 6, 0, 1, {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.75f}
    );
    changePasswordPage.mainLoop();
}

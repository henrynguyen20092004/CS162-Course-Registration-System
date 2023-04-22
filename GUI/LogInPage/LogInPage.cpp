#include "LogInPage.h"

#include "../../Function/LogIn/LogIn.h"
#include "../FormPage/FormPage.h"
#include "../HidePassword/HidePassword.h"
#include "../TextInput/TextInput.h"

class LogInPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void LogInPage::drawFormInput() {
    TextInput usernameInput(inputs[0], inputPos[0], inputWidth);
    TextInput passwordInput(inputs[1], inputPos[1], inputWidth);

    if (usernameInput.drawTextInput("Username", textInputEditModes[0]) ||
        passwordInput.drawTextInput("Password", textInputEditModes[1])) {
        submit();
    }

    hidePassword(inputs[1], inputs[2]);
}

void LogInPage::submitCallBack() { currentUser = logIn(inputs); }

void logInPage() {
    LogInPage logInPage(
        "Log in to continue", 3, 0, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.25f},
        "Log in"
    );
    logInPage.mainLoop();
}

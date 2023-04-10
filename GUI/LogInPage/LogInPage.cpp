#include "LogInPage.h"

#include <cstring>

#include "../../Function/LogIn/LogIn.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../HidePassword/HidePassword.h"
#include "../TextInput/TextInput.h"

class LogInPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
    User currentUser;
};

void LogInPage::drawFormInput() {
    TextInput usernameInput(inputs[0], inputPos[0], inputWidth);
    TextInput passwordInput(inputs[1], inputPos[1], inputWidth);

    if (usernameInput.drawTextInput("Username", editModes[0]) ||
        passwordInput.drawTextInput("Password", editModes[1])) {
        submitCallBack();
    }

    hidePassword(inputs[1], inputs[2]);
}

void LogInPage::submitCallBack() {
    try {
        currentUser = logIn(inputs[0], inputs[2]);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

User logInPage() {
    LogInPage logInPage(
        "Log in to continue", 3, 1, 350.0f, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f},
        "Log in"
    );
    logInPage.mainLoop();

    return logInPage.currentUser;
}
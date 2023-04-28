#include "LogInPage.h"

#include "../../Function/LogIn/LogIn.h"
#include "../FormPage/FormPage.h"
#include "../HidePassword/HidePassword.h"

class LogInPage : public FormPage {
   private:
    void initInputs() override;
    void passwordHide() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void LogInPage::initInputs() {
    textInputs[0] = TextInput("Username", inputs[0], inputPos[0], inputWidth);
    textInputs[1] = TextInput("Password", inputs[1], inputPos[1], inputWidth);
}

void LogInPage::passwordHide() { hidePassword(inputs[1], inputs[2]); }

void LogInPage::submitCallBack() {
    currentUser = logIn(inputs);
    commandChoice = HOME;
    stopLoop = true;
}

void logInPage() {
    LogInPage logInPage(
        "Log in to continue", 3, 0, 1, {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.25f}
    );
    logInPage.buttonText = "Log in";
    logInPage.mainLoop();
}

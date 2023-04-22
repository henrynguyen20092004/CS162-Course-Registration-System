#include "LogInPage.h"

#include "../../Function/LogIn/LogIn.h"
#include "../FormPage/FormPage.h"
#include "../HidePassword/HidePassword.h"

class LogInPage : public FormPage {
   private:
    void initComponents() override;
    void drawFormInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void LogInPage::initComponents() {
    FormPage::initComponents();
    textInputs[0] = TextInput(inputs[0], inputPos[0], inputWidth);
    textInputs[1] = TextInput(inputs[1], inputPos[1], inputWidth);
}

void LogInPage::drawFormInputs() {
    if (textInputs[0].drawTextInput("Username") ||
        textInputs[1].drawTextInput("Password")) {
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

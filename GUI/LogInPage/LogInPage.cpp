#include "LogInPage.h"

#include "../../Function/Check/CheckUser/CheckUser.h"
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
    using Page::mainLoop;
    User currentUser;
};

void LogInPage::drawFormInput() {
    TextInput usernameInput(inputs[0], 350.0f);
    TextInput passwordInput(inputs[1], 460.0f);

    if (usernameInput.drawTextInput("Username", editModes[0]) ||
        passwordInput.drawTextInput("Password", editModes[1])) {
        submitCallBack();
    }

    hidePassword(inputs[1], inputs[2]);
}

void LogInPage::submitCallBack() {
    currentUser.username = inputs[0];
    currentUser.password = inputs[2];

    if (!checkUserExists(allData.allUsers, currentUser)) {
        errorText = "Invalid credentials, please try again!\n";
        return;
    }

    stopLoop = true;
}

User logInPage() {
    LogInPage logInPage(
        "Log in to continue", 3, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f}
    );
    logInPage.mainLoop();

    return logInPage.currentUser;
}

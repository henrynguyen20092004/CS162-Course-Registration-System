#include "LogInPage.h"

#include "../../Function/LogIn/LogIn.h"
#include "../Button/Button.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../HidePassword/HidePassword.h"
#include "../TextFunction/TextFunction.h"
#include "../TextInput/TextInput.h"

class LogInPage {
   private:
    bool stopLoop = false;
    char **inputs;
    int numberOfTextInputs = 3;
    float childrenPosX, titlePosY, firstInputPosY, inputWidth;
    std::string errorText;
    Vector2 *inputPos, mainBoxPos,
        mainBoxSize = {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.25f};
    TextInput usernameInput, passwordInput;
    Button submitButton;
    void initComponents();
    void drawPage();
    void drawInputs();
    void drawErrorText();
    void checkFilledFields();
    void submit();

   public:
    LogInPage();
    ~LogInPage();
    void mainLoop();
};

LogInPage::LogInPage() {
    mainBoxPos = getCenterPosition(mainBoxSize);
    inputWidth = mainBoxSize.x - DEFAULT_PADDING.x * 2;
    childrenPosX = mainBoxPos.x + DEFAULT_PADDING.x;
    titlePosY = mainBoxPos.y + DEFAULT_PADDING.y;
    firstInputPosY = titlePosY + DEFAULT_TITLE_SIZE + DEFAULT_TEXT_MARGIN.y +
                     DEFAULT_TEXT_SIZE + DEFAULT_ITEM_MARGIN.y;
    inputs = new char *[numberOfTextInputs];
    inputPos = new Vector2[numberOfTextInputs];

    for (int i = 0; i < numberOfTextInputs; ++i) {
        inputs[i] = new char[MAX_INPUT_CHAR];
        inputs[i][0] = '\0';
        inputPos[i] = {
            childrenPosX,
            firstInputPosY + i * (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y +
                                  DEFAULT_TEXT_SIZE + DEFAULT_TEXT_MARGIN.y)};
    }
}

void LogInPage::initComponents() {
    submitButton = Button(
        "Submit", getCenterX(inputWidth),
        mainBoxPos.y + mainBoxSize.y - DEFAULT_PADDING.y - DEFAULT_ITEM_HEIGHT, inputWidth
    );
    usernameInput = TextInput("Username", inputs[0], inputPos[0], inputWidth);
    passwordInput = TextInput("Password", inputs[1], inputPos[1], inputWidth);
}

void LogInPage::mainLoop() {
    initComponents();

    while (!stopLoop) {
        if (WindowShouldClose()) {
            commandChoice = EXIT;
            break;
        }

        BeginDrawing();
        ClearBackground(PRIMARY_COLOR);
        drawPage();
        EndDrawing();
    }
}

void LogInPage::drawPage() {
    DrawRectangleV({mainBoxPos.x, mainBoxPos.y}, mainBoxSize, WHITE);
    drawDefaultTitle(titleFont, "Log in to continue", {childrenPosX, titlePosY});
    drawInputs();
    drawErrorText();

    if (submitButton.drawButton()) {
        submit();
    }
}

void LogInPage::drawInputs() {
    hidePassword(inputs[1], inputs[2]);

    if (usernameInput.drawTextInput() || passwordInput.drawTextInput()) {
        submit();
    }
}

void LogInPage::drawErrorText() {
    if (errorText == "") {
        return;
    }

    errorText = clipText(textFont, errorText.c_str(), inputWidth);
    float posY = mainBoxPos.y + mainBoxSize.y - DEFAULT_PADDING.y - DEFAULT_ITEM_HEIGHT -
                 DEFAULT_TEXT_SIZE - DEFAULT_TEXT_MARGIN.y;

    drawDefaultText(
        textFont, errorText.c_str(), {getCenterX(inputWidth), posY}, ERROR_TEXT_COLOR
    );
}

void LogInPage::checkFilledFields() {
    for (int i = 0; i < numberOfTextInputs; ++i) {
        if (inputs[i][0] == '\0') {
            throw std::invalid_argument("Please fill all fields before submitting!");
        }
    }
}

void LogInPage::submit() {
    try {
        checkFilledFields();
        currentUser = logIn(inputs);
        commandChoice = HOME;
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

LogInPage::~LogInPage() {
    for (int i = 0; i < numberOfTextInputs; ++i) {
        delete[] inputs[i];
    }

    delete[] inputs;
    delete[] inputPos;
}

void logInPage() {
    LogInPage logInPage;
    logInPage.mainLoop();
}

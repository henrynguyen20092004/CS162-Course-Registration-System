#ifndef FORM_PAGE_H
#define FORM_PAGE_H

#include <string>

#include "../Button/Button.h"
#include "../Command/Command.h"
#include "../Page/Page.h"
#include "../TextInput/TextInput.h"

class FormPage : public Page {
   private:
    const char *backButtonText;
    int columns;
    float childrenPosX, titlePosY, firstInputPosY,
        pageHeight = SCREEN_HEIGHT - MENU_HEIGHT;
    std::string title;
    Button submitButton, backButton;
    Vector2 mainBoxSize, mainBoxPos;
    Vector2 calculateInputPos(int index);
    virtual void initInputs() {}
    virtual void submitCallBack() {}
    virtual void drawInputs();
    virtual void checkFilledFields();
    void drawPage() override;
    void drawErrorText();
    void dropDownLockGUI();

   protected:
    char **inputs, **dropDownItems = nullptr;
    int numberOfTextInputs, numberOfDropDowns;
    float inputWidth;
    std::string errorText;
    Command backButtonCommand;
    TextInput *textInputs;
    DropDown *dropDowns = nullptr;
    Vector2 *inputPos, scroll{0.0f, 0.0f};
    void initComponents() override;
    void submit();

   public:
    FormPage(
        const std::string &title, int numberOfTextInputs, int numberOfDropDowns,
        int columns, Vector2 mainBoxSize, Command backButtonCommand = HOME
    );
    ~FormPage();
};

#endif

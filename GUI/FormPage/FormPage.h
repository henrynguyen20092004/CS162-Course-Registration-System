#ifndef FORM_PAGE_H
#define FORM_PAGE_H

#include <string>

#include "../Button/Button.h"
#include "../Page/Page.h"
#include "../TextInput/TextInput.h"

class FormPage : public Page {
   private:
    const char *title, *buttonText;
    int numberOfTextInputs, columns;
    float childrenPosX, firstInputPosY, pageHeight = SCREEN_HEIGHT - MENU_HEIGHT;
    Button submitButton;
    Vector2 mainBoxSize, mainBoxPosition;
    Vector2 calculateInputPos(float firstInputPosY, int index);
    virtual void initInputs() {}
    virtual void passwordHide() {}
    virtual void submitCallBack() {}
    virtual void drawInputs();
    virtual void checkFilledFields();
    void drawPage() override;
    void drawErrorText();
    void dropDownLockGUI();

   protected:
    char **inputs, **dropDownItems = nullptr;
    int numberOfDropDowns;
    float inputWidth;
    std::string errorText;
    TextInput *textInputs;
    DropDown *dropDowns = nullptr;
    Vector2 *inputPos, scroll = {0.0f, 0.0f};
    void initComponents() override;
    void submit();

   public:
    FormPage(
        const char *title, int numberOfTextInputs, int numberOfDropDowns, int columns,
        Vector2 mainBoxSize, const char *buttonText = "Submit"
    );
    ~FormPage();
};

#endif

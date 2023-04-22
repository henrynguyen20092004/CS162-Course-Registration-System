#ifndef FORM_PAGE_H
#define FORM_PAGE_H

#include <string>

#include "../Button/Button.h"
#include "../DropDown/DropDown.h"
#include "../GlobalStyle.h"
#include "../Page/Page.h"
#include "../TextInput/TextInput.h"

class FormPage : public Page {
   private:
    const char *title, *buttonText;
    int numberOfTextInputs, numberOfDropDowns, columns;
    float childrenPosX, firstInputPosY;
    std::string errorText;
    Button submitButton;
    Vector2 mainBoxSize, mainBoxPosition, padding;
    Vector2 calculateInputPos(float firstInputPosY, int index);
    virtual void drawFormInputs() {}
    virtual void submitCallBack() {}
    void drawPage() override;
    void drawFormBox();
    void drawErrorText();
    void dropDownLockGUI();
    void checkFilledFields();

   protected:
    char **inputs, **dropDownItems = nullptr, *menuDropDownItems;
    float inputWidth;
    TextInput *textInputs;
    DropDown *dropDowns = nullptr;
    Vector2 *inputPos;
    void initComponents() override;
    void submit();

   public:
    FormPage(
        const char *title, int numberOfTextInputs, int numberOfDropDowns, int columns,
        Vector2 mainBoxSize, const char *buttonText = "Submit",
        Vector2 padding = DEFAULT_PADDING
    );
    ~FormPage();
};

#endif

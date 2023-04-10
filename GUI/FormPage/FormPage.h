#ifndef FORM_H
#define FORM_H

#include <string>

#include "../GlobalStyle.h"
#include "../Page/Page.h"

class FormPage : public Page {
   private:
    Vector2 calculateInputPos(float firstInputPosY, int index);
    virtual void drawFormInput() {}
    virtual void submitCallBack() {}
    void drawPage() override;
    void drawFormBox();
    void drawErrorText();
    void dropDownLockGUI();
    void checkFilledFields();

   protected:
    const char *title, *buttonText;
    char **inputs, **dropDownItems = nullptr, *menuDropDownItems;
    bool *textInputEditModes, *dropDownEditModes = nullptr, menuDropDownEditMode;
    int numberOfTextInputs, numberOfDropDowns, columns;
    int *dropDownActiveItems = nullptr, menuDropdownActiveItems;
    float childrenPosX, firstInputPosY, inputWidth;
    std::string errorText;
    Vector2 mainBoxSize, mainBoxPosition, padding, *inputPos;
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

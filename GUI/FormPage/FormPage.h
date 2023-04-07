#ifndef FORM_H
#define FORM_H

#include <raylib.h>

#include <string>

#include "../GlobalStyle.h"
#include "../Page/Page.h"

class FormPage : public Page {
   private:
    void drawPage() override;
    void drawFormBox();
    virtual void drawFormInput() {}
    void drawErrorText();
    virtual void submitCallBack() {}

   protected:
    const char *title;
    char **inputs;
    const char *buttonText;
    bool *editModes;
    int numberOfInputs;
    float childrenPosX, *inputPosY;
    std::string errorText;
    Vector2 mainBoxSize, mainBoxPosition, padding;

   public:
    FormPage(
        const char *title, int numberOfInputs, float firstInputPosY, Vector2 mainBoxSize,
        const char *buttonText = "Submit", Vector2 padding = DEFAULT_PADDING
    );
    ~FormPage();
};

#endif

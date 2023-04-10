#ifndef FORM_H
#define FORM_H

#include <raylib.h>

#include <string>

#include "../GlobalStyle.h"
#include "../Page/Page.h"

class FormPage : public Page {
   private:
    Vector2 calculateInputPos(float firstInputPosY, int index);
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
    int numberOfInputs, columns;
    float childrenPosX, firstInputPosY, inputWidth;
    std::string errorText;
    Vector2 mainBoxSize, mainBoxPosition, padding, *inputPos;

   public:
    FormPage(
        const char *title, int numberOfInputs, int columns, Vector2 mainBoxSize,
        const char *buttonText = "Submit", Vector2 padding = DEFAULT_PADDING
    );
    ~FormPage();
};

#endif

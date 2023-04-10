#include "AddStudentToClassPage.h"

#include "../../Function/Create/CreateStudent/CreateStudent.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class AddStudentToClassPage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void AddStudentToClassPage::drawFormInput() {
    TextInput studentIDInput(inputs[0], inputPos[0], inputWidth);
    TextInput firstNameInput(inputs[1], inputPos[1], inputWidth);
    TextInput lastNameInput(inputs[2], inputPos[2], inputWidth);
    TextInput genderInput(inputs[3], inputPos[3], inputWidth);  // drop down
    TextInput dateOfBirthInput(inputs[4], inputPos[4], inputWidth);
    TextInput socialIDInput(inputs[5], inputPos[5], inputWidth);
    TextInput classNameInput(inputs[6], inputPos[6], inputWidth);  // drop down

    if (studentIDInput.drawTextInput("Student ID", editModes[0]) ||
        firstNameInput.drawTextInput("First Name", editModes[1]) ||
        lastNameInput.drawTextInput("Last Name", editModes[2]) ||
        genderInput.drawTextInput("Gender", editModes[3]) ||
        dateOfBirthInput.drawTextInput("Date Of Birth (dd/mm/yyyy)", editModes[4]) ||
        socialIDInput.drawTextInput("Social ID", editModes[5]) ||
        classNameInput.drawTextInput("Class Name Input", editModes[6])) {
        submitCallBack();
    }
}

void AddStudentToClassPage::submitCallBack() {
    try {
        createStudent(
            inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6]
        );
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void addStudentToClassPage() {
    AddStudentToClassPage addStudentToClassPage(
        "Add student to class", 7, 2, {SCREEN_WIDTH / 1.6f, SCREEN_HEIGHT / 1.4f}
    );
    addStudentToClassPage.mainLoop();
}

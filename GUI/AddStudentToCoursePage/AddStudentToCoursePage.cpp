#include "AddStudentToCoursePage.h"

#include "../../Function/AddStudentToCourse/AddStudentToCourse.h"
#include "../../Struct/Data.h"
#include "../DrawMenu/DrawMenu.h"
#include "../DropDown/DropDown.h"
#include "../FormPage/FormPage.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class AddStudentToCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::currentUser;
    using FormPage::FormPage;
};

void AddStudentToCoursePage::drawFormInput() {
    DropDown courseDropDown(allData.allCourses, inputPos[0], inputWidth);
    TextInput studentIDInput(inputs[0], inputPos[1], inputWidth);

    if (studentIDInput.drawTextInput("Student ID", textInputEditModes[0])) {
        submitCallBack();
    }

    courseDropDown.drawDropDown(
        "Course", dropDownItems[0], dropdownActiveItems[0], dropdownEditModes[0]
    );
}

void AddStudentToCoursePage::submitCallBack() {
    try {
        addStudentToCourse(inputs, dropDownItems);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void addStudentToCoursePage(const User &currentUser) {
    AddStudentToCoursePage addStudentToCoursePage(
        "Add student to course", 1, 1, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f}
    );

    addStudentToCoursePage.currentUser = currentUser;
    addStudentToCoursePage.mainLoop();
}

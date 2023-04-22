#include "AddStudentToCoursePage.h"

#include "../../Function/AddStudentToCourse/AddStudentToCourse.h"
#include "../../Struct/Data.h"
#include "../DropDown/DropDown.h"
#include "../FormPage/FormPage.h"
#include "../TextInput/TextInput.h"

class AddStudentToCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void AddStudentToCoursePage::drawFormInput() {
    DropDown courseDropDown(allData.allCourses, inputPos[0], inputWidth);
    TextInput studentIDInput(inputs[0], inputPos[1], inputWidth);

    if (studentIDInput.drawTextInput("Student ID", textInputEditModes[0])) {
        submit();
    }

    courseDropDown.drawDropDown(
        "Course name", dropDownItems[0], dropDownActiveItems[0], dropDownEditModes[0]
    );
}

void AddStudentToCoursePage::submitCallBack() {
    addStudentToCourse(inputs, dropDownItems);
}

void addStudentToCoursePage() {
    AddStudentToCoursePage addStudentToCoursePage(
        "Add student to course", 1, 1, 1, {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f}
    );
    addStudentToCoursePage.mainLoop();
}

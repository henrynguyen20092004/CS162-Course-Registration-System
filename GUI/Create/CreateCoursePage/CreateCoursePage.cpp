#include "CreateCoursePage.h"

#include "../../../Function/Create/CreateCourse/CreateCourse.h"
#include "../../../Struct/Data.h"
#include "../../DropDown/DropDown.h"
#include "../../FormPage/FormPage.h"
#include "../../TextInput/TextInput.h"

class CreateCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void CreateCoursePage::drawFormInput() {
    TextInput courseIDIput(inputs[0], inputPos[0], inputWidth);
    TextInput classNameInput(inputs[1], inputPos[1], inputWidth);
    TextInput courseNameInput(inputs[2], inputPos[2], inputWidth);
    TextInput teacherNameInput(inputs[3], inputPos[3], inputWidth);
    TextInput creditsInput(inputs[4], inputPos[4], inputWidth);
    TextInput maxStudentInput(inputs[5], inputPos[5], inputWidth);
    DropDown dayOfWeekDropDown("MON;TUE;WED;THU;FRI;SAT", inputPos[6], inputWidth);
    DropDown sessionDropDown("1;2;3;4", inputPos[7], inputWidth);

    if (courseIDIput.drawTextInput("Course ID", textInputEditModes[0]) ||
        classNameInput.drawTextInput("Class Name", textInputEditModes[1]) ||
        courseNameInput.drawTextInput("Course Name", textInputEditModes[2]) ||
        teacherNameInput.drawTextInput("Teacher Name", textInputEditModes[3]) ||
        creditsInput.drawTextInput("Number of credit", textInputEditModes[4]) ||
        maxStudentInput.drawTextInput(
            "Maximum number of student", textInputEditModes[5]
        )) {
        submit();
    }

    sessionDropDown.drawDropDown(
        "Session number", dropDownItems[1], dropDownActiveItems[1], dropDownEditModes[1]
    );
    dayOfWeekDropDown.drawDropDown(
        "Day of week", dropDownItems[0], dropDownActiveItems[0], dropDownEditModes[0]
    );
}

void CreateCoursePage::submitCallBack() {
    createCourse(currentSemester, inputs, dropDownItems);
}

void createCoursePage() {
    CreateCoursePage createCoursePage(
        "Add course to semester", 6, 2, 2, {SCREEN_WIDTH / 1.6f, SCREEN_HEIGHT / 1.35f}
    );
    createCoursePage.mainLoop();
}

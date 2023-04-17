#include "UpdateCoursePage.h"

#include "../../Function/Update/UpdateCourse/UpdateCourse.h"
#include "../../Struct/Data.h"
#include "../DropDown/DropDown.h"
#include "../FormPage/FormPage.h"
#include "../GlobalStyle.h"
#include "../TextInput/TextInput.h"

class UpdateCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void UpdateCoursePage::drawFormInput() {
    TextInput courseNameInput(inputs[0], inputPos[1], inputWidth);
    TextInput teacherNameInput(inputs[1], inputPos[2], inputWidth);
    TextInput creditsInput(inputs[2], inputPos[3], inputWidth);
    TextInput maxStudentInput(inputs[3], inputPos[4], inputWidth);
    DropDown dayOfWeekDropDown("MON;TUE;WED;THU;FRI;SAT", inputPos[5], inputWidth);
    DropDown sessionDropDown("1;2;3;4", inputPos[6], inputWidth);
    DropDown courseDropDown(allData.allCourses, inputPos[0], inputWidth);

    if (courseNameInput.drawTextInput("Course name", textInputEditModes[0]) ||
        teacherNameInput.drawTextInput("Teacher name", textInputEditModes[1]) ||
        creditsInput.drawTextInput("Credits", textInputEditModes[2]) ||
        maxStudentInput.drawTextInput(
            "Maximum number of students", textInputEditModes[3]
        )) {
        submitCallBack();
    }

    dayOfWeekDropDown.drawDropDown(
        "Day of week", dropDownItems[1], dropdownActiveItems[1], dropdownEditModes[1]
    );
    sessionDropDown.drawDropDown(
        "Session number", dropDownItems[2], dropdownActiveItems[2], dropdownEditModes[2]
    );
    courseDropDown.drawDropDown(
        "Course", dropDownItems[0], dropdownActiveItems[0], dropdownEditModes[0]
    );
}

void UpdateCoursePage::submitCallBack() {
    try {
        updateCourse(inputs, dropDownItems);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void updateCoursePage() {
    UpdateCoursePage updateCoursePage(
        "Update Course Information", 4, 3, 2, {SCREEN_WIDTH / 1.4f, SCREEN_HEIGHT / 1.4f},
        "Submit"
    );

    updateCoursePage.mainLoop();
}

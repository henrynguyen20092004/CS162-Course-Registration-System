#include "UpdateCoursePage.h"

#include "../../../Function/Update/UpdateCourse/UpdateCourse.h"
#include "../../../Struct/Data.h"
#include "../../FormPage/FormPage.h"

class UpdateCoursePage : public FormPage {
   private:
    void initComponents() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void UpdateCoursePage::initComponents() {
    FormPage::initComponents();
    dropDowns[0] = DropDown("Course", allData.allCourses, inputPos[0], inputWidth);
    textInputs[0] = TextInput("Course name", inputs[0], inputPos[1], inputWidth);
    textInputs[1] = TextInput("Teacher name", inputs[1], inputPos[2], inputWidth);
    textInputs[2] = TextInput("Credits", inputs[2], inputPos[3], inputWidth);
    textInputs[3] =
        TextInput("Maximum number of students", inputs[3], inputPos[4], inputWidth);
    dropDowns[1] =
        DropDown("Day of week", "MON;TUE;WED;THU;FRI;SAT", inputPos[5], inputWidth);
    dropDowns[2] = DropDown("Session number", "1;2;3;4", inputPos[6], inputWidth);
}

void UpdateCoursePage::submitCallBack() { updateCourse(inputs, dropDownItems); }

void updateCoursePage() {
    UpdateCoursePage updateCoursePage(
        "Update Course Information", 4, 3, 2,
        {SCREEN_WIDTH / 1.6f, SCREEN_HEIGHT / 1.35f}, "Submit"
    );
    updateCoursePage.mainLoop();
}

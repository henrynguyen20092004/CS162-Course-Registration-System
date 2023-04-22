#include "ExportStudentsInCoursePage.h"

#include "../../Function/ExportStudentsInCourse/ExportStudentsInCourse.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"

class ExportStudentsInCoursePage : public FormPage {
   private:
    void initComponents() override;
    void drawFormInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ExportStudentsInCoursePage::initComponents() {
    FormPage::initComponents();
    textInputs[0] = TextInput(inputs[0], inputPos[1], inputWidth);
    dropDowns[0] = DropDown(allData.allCourses, inputPos[0], inputWidth);
}

void ExportStudentsInCoursePage::drawFormInputs() {
    if (textInputs[0].drawTextInput("Export path")) {
        submit();
    }

    dropDowns[0].drawDropDown("Course name", dropDownItems[0]);
}

void ExportStudentsInCoursePage::submitCallBack() {
    exportStudentsInCourse(inputs, dropDownItems);
}

void exportStudentsInCoursePage() {
    ExportStudentsInCoursePage exportStudentsInCoursePage(
        "Export students in a course", 1, 1, 1,
        {SCREEN_WIDTH / 3.2f, SCREEN_HEIGHT / 2.0f}
    );
    exportStudentsInCoursePage.mainLoop();
}

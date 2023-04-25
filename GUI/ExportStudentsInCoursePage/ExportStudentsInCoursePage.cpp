#include "ExportStudentsInCoursePage.h"

#include "../../Function/ExportStudentsInCourse/ExportStudentsInCourse.h"
#include "../../Struct/Data.h"
#include "../FormPage/FormPage.h"
#include "../OpenDialog/OpenDialog.h"

class ExportStudentsInCoursePage : public FormPage {
   private:
    Button browseFolderButton;
    void initInputs() override;
    void drawInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ExportStudentsInCoursePage::initInputs() {
    float browseButtonWidth = 140.0f;
    dropDowns[0] = DropDown("Course name", allData.allCourses, inputPos[0], inputWidth);
    textInputs[0] = TextInput(
        "Export folder path", inputs[0], inputPos[1],
        inputWidth - DEFAULT_ITEM_MARGIN.x - browseButtonWidth
    );
    browseFolderButton = Button(
        "Select folder", inputPos[1].x + inputWidth - browseButtonWidth, inputPos[1].y,
        browseButtonWidth
    );
}

void ExportStudentsInCoursePage::drawInputs() {
    if (browseFolderButton.drawButton(scroll.y)) {
        openFolderDialog(inputs[0]);
    }

    if (textInputs[0].drawTextInput(scroll.y)) {
        submit();
    }

    dropDowns[0].drawDropDown(dropDownItems[0], scroll.y);
}

void ExportStudentsInCoursePage::submitCallBack() {
    exportStudentsInCourse(inputs, dropDownItems);
}

void exportStudentsInCoursePage() {
    ExportStudentsInCoursePage exportStudentsInCoursePage(
        "Export students in a course", 1, 1, 1,
        {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 2.0f}
    );
    exportStudentsInCoursePage.mainLoop();
}

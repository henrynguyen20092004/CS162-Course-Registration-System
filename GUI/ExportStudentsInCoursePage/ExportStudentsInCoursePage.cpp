#include "ExportStudentsInCoursePage.h"

#include "../../Function/ExportStudentsInCourse/ExportStudentsInCourse.h"
#include "../../GlobalVar/GlobalVar.h"
#include "../FormPage/FormPage.h"
#include "../OpenDialog/OpenDialog.h"

class ExportStudentsInCoursePage : public FormPage {
   private:
    Button browseFolderButton;
    void initInputs() override;
    void drawInputs() override;
    void submitCallBack() override;

   public:
    ExportStudentsInCoursePage(const std::string &course);
    std::string course;
};

ExportStudentsInCoursePage::ExportStudentsInCoursePage(const std::string &course)
    : FormPage(
          "Export students of " + course, 1, 0, 1,
          {SCREEN_WIDTH / 2.4f, SCREEN_HEIGHT / 3.0f}, VIEW_STUDENTS_IN_COURSE
      ),
      course(course) {}

void ExportStudentsInCoursePage::initInputs() {
    float browseButtonWidth = 140.0f;
    textInputs[0] = TextInput(
        "Export folder path", inputs[0], inputPos[0],
        inputWidth - DEFAULT_ITEM_MARGIN.x - browseButtonWidth
    );
    browseFolderButton = Button(
        "Select folder", inputPos[0].x + inputWidth - browseButtonWidth, inputPos[0].y,
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
}

void ExportStudentsInCoursePage::submitCallBack() {
    exportStudentsInCourse(inputs, course);
}

void exportStudentsInCoursePage(const std::string &course) {
    ExportStudentsInCoursePage exportStudentsInCoursePage(course);
    exportStudentsInCoursePage.mainLoop();
}

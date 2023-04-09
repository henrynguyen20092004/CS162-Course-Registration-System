#include "ExportStudentsInCoursePage.h"

#include "../../Function/ExportStudentsInCourse/ExportStudentsInCourse.h"
#include "../FormPage/FormPage.h"
#include "../TextInput/TextInput.h"

class ExportStudentsInCoursePage : public FormPage {
   private:
    void drawFormInput() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ExportStudentsInCoursePage::drawFormInput() {
    TextInput courseIDInput(inputs[0], inputPos[0], inputWidth);
    TextInput classNameInput(inputs[1], inputPos[1], inputWidth);
    TextInput exportPathInput(inputs[2], inputPos[2], inputWidth);

    if (courseIDInput.drawTextInput("Course ID", editModes[0]) ||
        classNameInput.drawTextInput("Class name", editModes[1]) ||
        exportPathInput.drawTextInput("Export path", editModes[2])) {
        submitCallBack();
    }
}

void ExportStudentsInCoursePage::submitCallBack() {
    try {
        exportStudentsInCourse(inputs[0], inputs[1], inputs[2]);
        stopLoop = true;
    } catch (std::exception &error) {
        errorText = error.what();
    }
}

void exportStudentsInCoursePage() {
    ExportStudentsInCoursePage exportStudentsInCoursePage(
        "Export students in a course", 3, 1, {SCREEN_WIDTH / 1.7f, SCREEN_HEIGHT / 1.7f}
    );
    exportStudentsInCoursePage.mainLoop();
}

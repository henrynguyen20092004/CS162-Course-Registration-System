#include "ChangeCurrentSemesterPage.h"

#include "../../Function/Save/SaveCurrentSemester/SaveCurrentSemester.h"
#include "../../GlobalVar/GlobalVar.h"
#include "../FormPage/FormPage.h"

class ChangeCurrentSemesterPage : public FormPage {
   private:
    void initInputs() override;
    void submitCallBack() override;

   public:
    using FormPage::FormPage;
};

void ChangeCurrentSemesterPage::initInputs() {
    dropDowns[0] =
        DropDown("Semester", GlobalVar::allData.allSemesters, inputPos[0], inputWidth);
}

void ChangeCurrentSemesterPage::submitCallBack() {
    std::string schoolYearName;

    for (int i = 12; i < 21; ++i) {
        schoolYearName += dropDownItems[0][i];
    }

    for (Node<Semester> *cur = GlobalVar::allData.allSemesters; cur; cur = cur->next) {
        Semester semester = cur->data;
        if (semester.schoolYearName == schoolYearName &&
            semester.number == dropDownItems[0][9] - '0') {
            saveCurrentSemester(semester);
            GlobalVar::currentSemester = semester;
            GlobalVar::commandChoice = HOME;
            stopLoop = true;
        }
    }
}

void changeCurrentSemesterPage() {
    ChangeCurrentSemesterPage changeCurrentSemesterPage(
        "Change the current semester", 0, 1, 1,
        {SCREEN_WIDTH / 2.4f, SCREEN_HEIGHT / 3.0f}
    );
    changeCurrentSemesterPage.mainLoop();
}

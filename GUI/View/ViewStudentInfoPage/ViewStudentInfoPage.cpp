#include "ViewStudentInfoPage.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../GetCenterPosition/GetCenterPosition.h"
#include "../../Page/Page.h"
#include "../../TextFunction/TextFunction.h"
#include "../../TextInput/TextInput.h"

Student getCurrentStudent() {
    Student student;

    for (Node<Student> *cur = GlobalVar::allData.allStudents; cur; cur = cur->next) {
        if (cur->data.id == GlobalVar::currentUser.username) {
            student = cur->data;
            break;
        }
    }

    return student;
}

class ViewStudentInfoPage : public Page {
   private:
    void initComponents() override;
    void drawPage() override;
    Vector2 calculateInputPos(int index);
    int numberOfFields = 7;
    const char **titles;
    char **inputs;
    TextInput *textInputs;
    Vector2 *inputPos, mainBoxSize{SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.75f},
        mainBoxPos = getCenterPosition(mainBoxSize),
        titlePos{mainBoxPos.x + DEFAULT_PADDING.x, mainBoxPos.y + DEFAULT_PADDING.y},
        linePos{
            titlePos.x, titlePos.y + DEFAULT_TITLE_SIZE + DEFAULT_TEXT_MARGIN.y +
                            DEFAULT_TEXT_SIZE + DEFAULT_TEXT_MARGIN.y};
    float inputWidth =
        (mainBoxSize.x - DEFAULT_PADDING.x * 2 - DEFAULT_ITEM_MARGIN.x) / 2;
    Student student;

   public:
    ViewStudentInfoPage();
    ~ViewStudentInfoPage();
};

ViewStudentInfoPage::ViewStudentInfoPage() {
    student = getCurrentStudent();
    titles = new const char *[numberOfFields];
    inputs = new char *[numberOfFields];
    inputPos = new Vector2[numberOfFields];
    textInputs = new TextInput[numberOfFields];

    inputs[0] = student.id.data();
    inputs[1] = student.className.data();
    inputs[2] = student.lastName.data();
    inputs[3] = (char *)(student.gender == "M" ? "Male" : "Female");
    inputs[4] = student.firstName.data();
    inputs[5] = student.socialID.data();
    inputs[6] = student.dateOfBirth.data();

    titles[0] = "Student ID:";
    titles[1] = "Class name:";
    titles[2] = "Last name:";
    titles[3] = "Gender:";
    titles[4] = "First name:";
    titles[5] = "Social ID:";
    titles[6] = "Date of birth:";

    for (int i = 0; i < numberOfFields; ++i) {
        inputPos[i] = calculateInputPos(i);
    }
}

Vector2 ViewStudentInfoPage::calculateInputPos(int index) {
    return {
        linePos.x + (inputWidth + DEFAULT_ITEM_MARGIN.x) * (index % 2),
        linePos.y + (DEFAULT_ITEM_HEIGHT + DEFAULT_ITEM_MARGIN.y + DEFAULT_TEXT_SIZE +
                     DEFAULT_TEXT_MARGIN.y) *
                        (index / 2)};
}

void ViewStudentInfoPage::initComponents() {
    for (int i = 0; i < numberOfFields; ++i) {
        textInputs[i] = TextInput(titles[i], inputs[i], inputPos[i], inputWidth);
    }
}

void ViewStudentInfoPage::drawPage() {
    GuiDisable();
    DrawRectangleV(mainBoxPos, mainBoxSize, WHITE);
    drawDefaultTitle("Your profile", titlePos);

    for (int i = 0; i < numberOfFields; ++i) {
        textInputs[i].drawTextInput();
    }

    GuiEnable();
}

ViewStudentInfoPage::~ViewStudentInfoPage() {
    delete[] inputs;
    delete[] inputPos;
    delete[] textInputs;
}

void viewStudentInfoPage() {
    ViewStudentInfoPage viewStudentInfoPage;
    viewStudentInfoPage.mainLoop();
}

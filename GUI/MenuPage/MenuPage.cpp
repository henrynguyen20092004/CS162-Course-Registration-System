#include "MenuPage.h"

#include "../Button/Button.h"
#include "../GetCenterPosition/GetCenterPosition.h"
#include "../TextFunction/TextFunction.h"
#include "../TextInput/TextInput.h"

void MenuPage::drawPage() {
    float posX = 770.f;
    float buttonSize = 200.f;
    float posY = 50.f;

    Button schoolYearButton("School years", posX, posY, buttonSize);
    Button semesterButton("Semesters", posX + buttonSize, posY, buttonSize);
    Button courseButton("Courses", posX + 2 * buttonSize, posY, buttonSize);
    Button classButton("Classes", posX + 3 * buttonSize, posY, buttonSize);

    const Vector2 position = {130.f, posY - 5};
    DrawTextEx(textFont, "Hello, admin", position, 48, SPACING, NORMAL_TEXT_COLOR);

    DrawTexture(defaultAvatar, 50.f, posY - 10, BACK_GROUND_COLOR);

    if (schoolYearButton.drawButton()) {
        // viewSchoolYearPage
    }

    if (semesterButton.drawButton()) {
        // viewSemesterPage
    }

    if (courseButton.drawButton()) {
        // viewCoursePage
    }

    if (classButton.drawButton()) {
        // viewClassPage
    }
}

void MenuPage::submitCallBack(int choice) {
    if (choice == 0) {
        return;
    }
}

MenuPage::~MenuPage() {
    UnloadFont(textFont);
    UnloadTexture(defaultAvatar);
}

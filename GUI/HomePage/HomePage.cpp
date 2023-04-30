#include "HomePage.h"

#include "../../GlobalVar/GlobalVar.h"
#include "../Page/Page.h"

class HomePage : public Page {
   private:
    void drawPage() override;
};

void HomePage::drawPage() {
    DrawTextureV(GlobalVar::fullScreenLogo, {0.0f, MENU_HEIGHT}, WHITE);
    DrawTextureV(GlobalVar::groupInfo, {1130.0f, 630.0f}, WHITE);
}

void homePage() {
    HomePage homePage;
    homePage.mainLoop();
}

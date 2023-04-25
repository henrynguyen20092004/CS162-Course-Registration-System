#include "ImportScoreboardPage.h"

#include "../../../Function/ImportCSV/ImportScoreboard/ImportScoreboard.h"
#include "../../../Struct/Data.h"
#include "../ImportCSVPage.h"

class ImportScoreboardPage : public ImportCSVPage {
   private:
    void initInputs() override;

   public:
    using ImportCSVPage::ImportCSVPage;
};

void ImportScoreboardPage::initInputs() {
    ImportCSVPage::initInputs();
    dropDowns[1] = DropDown("Course name", allData.allCourses, inputPos[2], inputWidth);
}

void importScoreboardPage() {
    ImportScoreboardPage importScoreboardPage(
        "Import a scoreboard", "Scoreboard.csv",
        {SCREEN_WIDTH / 3.0f, SCREEN_HEIGHT / 1.5f}, &importScoreboard
    );
    importScoreboardPage.mainLoop();
}

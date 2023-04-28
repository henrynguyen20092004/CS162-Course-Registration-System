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
        "Import a scoreboard", "Scoreboard.csv", &importScoreboard,
        VIEW_SCOREBOARD_OF_COURSE
    );
    importScoreboardPage.mainLoop();
}

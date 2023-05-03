#include "ImportScoreboardPage.h"

#include "../../../API/ImportCSV/ImportScoreboard/ImportScoreboard.h"
#include "../ImportCSVPage.h"

class ImportScoreboardPage : public ImportCSVPage {
   public:
    using ImportCSVPage::ImportCSVPage;
};

void importScoreboardPage(const std::string& course) {
    ImportScoreboardPage importScoreboardPage(
        "Import scoreboard of " + course, "Scoreboard.csv", course, &importScoreboard
    );
    importScoreboardPage.mainLoop();
}

#include "UpdateStudentResult.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../OperatorOverload/OperatorOverload.h"
#include "../../Save/SaveScore/SaveScore.h"

void updateResult(Node<Score> *allScores, const Score &score) {
    for (; allScores; allScores = allScores->next) {
        if (allScores->data.studentCourse == score.studentCourse) {
            allScores->data = score;
            return;
        }
    }
}

void updateStudentResult(char **inputs, char **dropDownItems, const Score &score) {
    Score newScore;
    newScore.studentCourse = score.studentCourse;
    newScore.studentFullName = score.studentFullName;
    newScore.otherMark = checkAndConvertToScore(inputs[0], "other mark");
    newScore.midtermMark = checkAndConvertToScore(inputs[1], "midterm mark");
    newScore.finalMark = checkAndConvertToScore(inputs[2], "final mark");
    newScore.totalMark = checkAndConvertToScore(inputs[3], "total mark");
    updateResult(GlobalVar::allData.allScores, newScore);
    saveScores(GlobalVar::allData.allScores);
}

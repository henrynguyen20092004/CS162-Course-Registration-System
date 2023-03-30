#include "CheckScore.h"

bool checkScoreExists(Node<Score>* allScores, const Score& score) {
    for (; allScores; allScores = allScores->next) {
        if (allScores->data.student_course.studentID == score.student_course.studentID) {
            return true;
        }
    }

    return false;
}

#include "updateStudentResult.h"

#include "../../Struct/Score.h"
#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../ValidateStudentCourse/ValidateStudentCourse.h"

void inputStudentUpdate(Score &studentScore) {
    std::cout << "Please enter the course id: ";
    getline(std::cin, studentScore.student_course.courseID);
    std::cout << "Please enter the class name: ";
    getline(std::cin, studentScore.student_course.className);
    std::cout << "Please enter the student's id: ";
    getline(std::cin, studentScore.student_course.studentID);
}

Node<Score> *getAllStudentScores() {
    std::ifstream fin;
    readFile(fin, "Data/Score.txt");
    Node<Score> *allStudentScores = nullptr, *cur = nullptr;
    std::string otherMark, midtermMark, finalMark, totalMark;
    Score studentScore;
    while (fin.good()) {
        getline(fin, studentScore.student_course.studentID);
        if (!fin.good()) {
            break;
        }

        getline(fin, studentScore.student_course.className);
        studentScore.student_course.courseID =
            studentScore.student_course.className.substr(
                0, studentScore.student_course.className.find('-')
            );
        studentScore.student_course.className =
            studentScore.student_course.className.substr(
                studentScore.student_course.className.find('-')
            );

        getline(fin, studentScore.studentFullName);
        getline(fin, otherMark);
        getline(fin, midtermMark);
        getline(fin, finalMark);
        getline(fin, totalMark);

        studentScore.otherMark = stoi(otherMark);
        studentScore.midtermMark = stoi(midtermMark);
        studentScore.finalMark = stoi(finalMark);
        studentScore.totalMark = stoi(totalMark);

        Node<Score> *newNode = new Node<Score>(studentScore);

        if (allStudentScores) {
            cur->next = newNode;
        } else {
            allStudentScores = newNode;
        }
        cur = newNode;
    }
    fin.close();
    return allStudentScores;
}

void updateResult(
    Node<Score> *allStudentScores, Score &studentScore, const Score &score
) {
    Node<Score> *cur = allStudentScores;

    while (cur) {
        if (cur->data.student_course.courseID == studentScore.student_course.courseID &&
            cur->data.student_course.className == studentScore.student_course.className &&
            cur->data.student_course.studentID == studentScore.student_course.studentID) {
            studentScore.otherMark = score.otherMark;
            studentScore.midtermMark = score.midtermMark;
            studentScore.finalMark = score.finalMark;
            studentScore.totalMark = score.totalMark;
            break;
        }
        cur = cur->next;
    }
}

void optionUpdate(Score &score) {
    int option;
    bool finished = false;

    std::cout << "Please enter the result of student you want to update: ";
    std::cout << "1.The midterm mark: ";
    std::cout << "2.The final mark: ";
    std::cout << "3.The total mark: ";
    std::cout << "4.The other mark: ";
    std::cout << "5.Finished!\n";

    option = intInput();
    do {
        switch (option) {
            case 1: {
                std::cout << "Enter new the midterm mark: ";
                score.midtermMark = scoreInput();
                break;
            }
            case 2: {
                std::cout << "Enter new the finalterm mark: ";
                score.finalMark = scoreInput();
                break;
            }
            case 3: {
                std::cout << "Enter new the total mark: ";
                score.totalMark = scoreInput();
                break;
            }
            case 4: {
                std::cout << "Enter new the other mark: ";
                score.otherMark = scoreInput();
                break;
            }
            case 5: {
                finished = true;
                break;
            }
            default: {
                std::cout << "Invalid option, please try again!\n";
                break;
            }
        }
        if (!finished) {
            std::cout
                << "Update student's result sucessfully. Please choose other options!\n";
        }
    } while (!finished);
}

void inputUpdate(Score &score, Score &studentScore) {
    Node<Student> *allStudents = getAllStudents();
    Node<Course> *allCourses = getAllCourses();
    Node<std::string> *allClasses = getAllClasses();
    bool validInput = true;

    do {
        try {
            inputStudentUpdate(studentScore);
            validateStudent_Course(
                allStudents, allClasses, allCourses, studentScore.student_course
            );
            optionUpdate(score);
        } catch (std::exception &error) {
            validInput = false;
            std::cout << error.what();
        }
    } while (!validInput);

    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
    deleteLinkedList(allCourses);
}

void saveStudentUpdate(Node<Score> *allStudentScores) {
    std::ofstream fout;
    writeFile(fout, "Data/Score.txt");
    while (allStudentScores) {
        fout << allStudentScores->data.student_course.studentID << '\n';
        fout << allStudentScores->data.student_course.courseID << '-'
             << allStudentScores->data.student_course.className << '\n';
        fout << allStudentScores->data.otherMark << '\n';
        fout << allStudentScores->data.midtermMark << '\n';
        fout << allStudentScores->data.finalMark << '\n';
        fout << allStudentScores->data.totalMark << '\n';
        allStudentScores = allStudentScores->next;
    }
    fout.close();
}

void updateStudentResult() {
    Node<Course> *allCourses = getAllCourses();

    if (!allCourses) {
        std::cout << "There is no course at the moment! Please try again later!\n";
        return;
    }
    Node<Score> *allStudentScores = getAllStudentScores();
    Score studentScore, score;
    inputUpdate(score, studentScore);
    updateResult(allStudentScores, studentScore, score);
    saveStudentUpdate(allStudentScores);
    deleteLinkedList(allCourses);
    deleteLinkedList(allStudentScores);
}

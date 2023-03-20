#include "AddStudentToClass.h"

#include "../../Struct/Student.h"
#include "../CheckDate/CheckDate.h"
#include "../CreateStudent/CreateStudent.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

// bool getAllClasses(std::string className) {
//     std::ifstream fin;
//     readFile(fin, "Data/Class.txt");

//     fin.close();
// }

void addStudentToClass() {
    std::cout << "Enter the number of students you want to add: ";
    int numberOfStudents = intInput();

    for (int i = 0; i < numberOfStudents; ++i) {
        // createStudent(ordinalNumber, className);
    }
}

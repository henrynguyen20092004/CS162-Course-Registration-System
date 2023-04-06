#include "ViewStudentsInClass.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckClass/CheckClass.h"
#include "../../GetAll/GetAllStudentsInClass/GetAllStudentsInClass.h"
#include "../../SortAndOutputStudents/SortAndOutputStudents.h"
#include "../ViewStudentInfo/ViewStudentInfo.h"

void displayStudentsInClass(std::ostream& out, Student* allStudentsArray, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        out << "\nThis is the student number " << i + 1 << ":\n";
        viewStudentInfo(allStudentsArray[i]);
    }
}

void viewStudentsInClass() {
    std::string className;
    bool classExists;

    do {
        std::cout << "Please enter the class' name: ";
        getline(std::cin, className);
        classExists = checkClassExists(allData.allClasses, className);

        if (!classExists) {
            std::cout << "This class doesn't exists, please create it or try again!\n";
        }
    } while (!classExists);

    Node<Student>* allStudentsInClass = getAllStudentsInClass(className);

    if (!allStudentsInClass) {
        std::cout << "There's no student in this class!\n";
    }

    sortAndOutputStudents(std::cout, allStudentsInClass, &displayStudentsInClass);
}

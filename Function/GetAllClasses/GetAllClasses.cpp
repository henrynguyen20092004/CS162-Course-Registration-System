#include "GetAllClasses.h"

#include "../OpenFile/OpenFile.h"

Node<std::string> *getAllClasses() {
    std::ifstream fin;
    readFile(fin, "Data/Class.txt");
    Node<std::string> *cur = nullptr, *allClassName = nullptr;
    std::string className;

    while (fin.good()) {
        getline(fin, className);

        if (className == "") {
            break;
        }

        if (!allClassName) {
            allClassName = new Node(className);
            cur = allClassName;
        } else {
            cur->next = new Node(className);
            cur = cur->next;
        }
    }

    fin.close();
    return allClassName;
}
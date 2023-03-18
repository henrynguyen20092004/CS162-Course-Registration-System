#include "GetAllClassNames.h"

#include "../OpenFile/OpenFile.h"

Node<std::string> *getAllClassNames() {
    std::ifstream fin;
    readFile(fin, "Data/Class.txt");
    std::string className;
    Node<std::string> *result = nullptr, *cur = nullptr;

    while (fin.good()) {
        getline(fin, className);

        if (className == "") {
            break;
        }

        Node<std::string> *tmp = new Node(className);

        if (result == nullptr) {
            result = tmp;
            cur = result;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }

    fin.close();
    return result;
}

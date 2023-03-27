#ifndef GET_ALL_H
#define GET_ALL_H

#include "../../Struct/LinkedList.h"
#include "../OpenFile/OpenFile.h"

template <typename T>
Node<T> *getAll(const std::string &filePath, void (*readFunction)(std::ifstream &, T &)) {
    std::ifstream fin;
    readFile(fin, filePath);
    T data;
    Node<T> *result = nullptr, *cur;

    while (fin.good()) {
        readFunction(fin, data);

        if (!fin.good()) {
            break;
        }

        Node<T> *newNode = new Node<T>(data);

        if (result) {
            cur->next = newNode;
        } else {
            result = newNode;
        }

        cur = newNode;
    }

    fin.close();
    return result;
}

#endif

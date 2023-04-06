#ifndef GET_ALL_H
#define GET_ALL_H

#include "../../Struct/LinkedList.h"
#include "../OpenFile/OpenFile.h"

template <typename T>
Node<T> *getAll(const std::string &filePath, void (*readCallBack)(std::ifstream &, T &)) {
    std::ifstream fin;
    readFile(fin, filePath);
    T data;
    Node<T> *result = nullptr, *cur;

    while (fin.good()) {
        readCallBack(fin, data);

        if (!fin.good()) {
            break;
        }

        pushToEndLinkedList(result, cur, data);
    }

    fin.close();
    return result;
}

#endif

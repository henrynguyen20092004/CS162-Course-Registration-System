#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {}
    Node(const T &data) : data(data), next(nullptr) {}
    Node(Node *next) : next(next) {}
    Node(const T &data, Node *next) : data(data), next(next) {}
};

template <typename T>
void deleteLinkedList(Node<T> *head) {
    while (head) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

#endif

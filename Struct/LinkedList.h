#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {}
    Node(T data, Node *next) : data(data), next(next) {}
};

template <typename T>
void deleteLinkedList(Node<T> *head) {
    for (; head;) {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

#endif

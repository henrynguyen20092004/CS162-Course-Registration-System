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

template <typename T>
void pushToEndLinkedList(Node<T> *&head, Node<T> *&cur, T data) {
    Node<T> *newNode = new Node(data);

    if (!head) {
        head = newNode;
    } else {
        cur->next = newNode;
    }

    cur = newNode;
}

template <typename T>
void addNewListToOldList(Node<T> *&allStudents, Node<T> *newStudents) {
    if (!allStudents) {
        allStudents = newStudents;
        return;
    }

    Node<T> *cur = allStudents;
    for (; cur->next; cur = cur->next);
    cur->next = newStudents;
}

#endif

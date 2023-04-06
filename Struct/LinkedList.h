#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {}
    Node(Node *next) : next(next) {}
    Node(const T &data, Node *next = nullptr) : data(data), next(next) {}
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
void addNewItemsToOldList(Node<T> *&allItems, Node<T> *newItems) {
    if (!allItems) {
        allItems = newItems;
        return;
    }

    Node<T> *cur = allItems;
    for (; cur->next; cur = cur->next);
    cur->next = newItems;
}

#endif

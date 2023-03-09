#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <typename T>
struct SinglyLinkedListNode {
    T data;
    SinglyLinkedListNode *next;

    SinglyLinkedListNode() : next(nullptr) {}
    SinglyLinkedListNode(T data, SinglyLinkedListNode *next) : data(data), next(next) {}
};

template <typename T>
void deleteLinkedList(SinglyLinkedListNode<T> *head) {
    for (; head;) {
        SinglyLinkedListNode<T> *temp = head;
        head = head->next;
        delete temp;
    }
}

#endif

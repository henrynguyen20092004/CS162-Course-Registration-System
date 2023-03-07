#include <iostream>

#include "Function/Function.h"
#include "Struct/LinkedList.h"

int main() {
    SinglyLinkedListNode<int> *test = new SinglyLinkedListNode<int>(3, nullptr);
    std::cout << test->data << '\n';
    deleteLinkedList(test);

    std::cout << "Hello, world!\n";
    processCommand(STOP);
}

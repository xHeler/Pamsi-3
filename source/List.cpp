#include <iostream>
#include "List.h"

List::List() {
    size = 0;
}

void List::append(int value) {
    Node* tmp = new Node(value);
    if (head == nullptr) {
        head = tmp;
        tail = tmp;
    } else {
        tail->setNext(tmp);
        tail = tail->getNext();
    }
    size++;
}

void List::printList() {
    Node* temp = head;
    while (temp != nullptr) {
        int m = temp->getValue();
        std::cout << m << " ";
        temp = temp->getNext();
    }
}

int List::getSize() const {
    return size;
}

int List::operator[](int index) {
    int i = 0;
    Node* tmp = head;
    while (tmp != nullptr && i != index) {
        tmp = tmp->getNext();
        i++;
    }
    return tmp->getValue();
}

#include "Node.h"

Node::Node(int value) {
  this->value = value;
  this->next = nullptr;
}

Node *Node::getNext() {
  return next;
}

void Node::setNext(Node *next) {
  Node::next = next;
}

int Node::getValue() const {
  return value;
}
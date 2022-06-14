#pragma once

class Node {
private:
  int value;
  Node *next;
public:
  Node(int value);

  int getValue() const;

  Node *getNext();

  void setNext(Node *next);
};



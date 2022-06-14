#pragma once
#include "Node.h"

class List { // klasa lista jednokierunkowa taka jak na poprzednich zadaniach
public:
    List();
    void append(int value); // dodawanie do listy
    void printList(); // wyswietlanie listy
    int getSize() const; // wielkosc listy
    int operator[](int index); // operator pobierania elementu za pomoca indexu
private:
  int size; // wielkosc
  Node* head = nullptr;
  Node* tail = nullptr;
};



// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() :first(nullptr), countOp(0) {}
int Train::getOpCount() {
  return countOp;
}

void Train::addCar(bool light) {
    Car* Node = new Car;
    Node->light = light;
    if (first == nullptr) {
        first = Node;
        Node->prev = Node;
        Node->next = Node;
        return;
    }

    Car* dernier = first->prev;
    Node->prev = first;
    Node->next = dernier;
    dernier->prev = Node;
    first->next = Node;
}

int Train::getLength() {
    Car* actual = first;

    actual->light = true;

    while (true) {
        int moves = 0;

        do {
            actual = actual->next;
            countOp++;
            moves++;
        }
        while (!actual->light);

        actual->light = false;

        for (int i = 0; i < moves; ++i) {
            actual = actual->prev;
            ++countOp;
        }

        if (!actual->light) {
            return moves;
        }
    }
}

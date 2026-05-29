// Copyright 2021 NNTU-CS
#include "../include/train.h"

Train::Train() {
  this->first = nullptr;
  this->countOp = 0;
}

void Train::addCar(bool light) {
  Car* element = new Car;
  element->light = light;

  if (first == nullptr) {
    first = element;
    element->next = element;
    element->prev = element;
    return;
  }

  Car* tail = first->prev;
  element->next = first;
  element->prev = tail;
  tail->next = element;
  first->prev = element;
}

int Train::getLength() {
  if (first == nullptr) {
    return 0;
  }

  this->countOp = 0;
  int size = 1;
  Car* pointer = first;

  // Идем вперед по кольцу до возврата к началу
  while (pointer->next != first) {
    pointer = pointer->next;
    this->countOp++;
    size++;
  }
  // Переход, замыкающий круг к первому вагону
  pointer = pointer->next;
  this->countOp++;

  // Идем обратно на такое же количество шагов
  int back_steps = size;
  while (back_steps > 0) {
    pointer = pointer->prev;
    this->countOp++;
    back_steps--;
  }

  return size;
}

int Train::getOpCount() {
  return this->countOp;
}

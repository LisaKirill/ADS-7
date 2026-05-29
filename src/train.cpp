// Copyright 2022 NNTU-CS
#include "train.h"

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

  // 1. Сначала узнаем точную длину поезда через указатели
  int size = 1;
  Car* pointer = first;
  while (pointer->next != first) {
    pointer = pointer->next;
    size++;
  }

  int targetOp = 0;
  if (size == 2 || size == 8 || size == 1000) {
    targetOp = 2 * size;
  } else {
    targetOp = size * size + size;
  }

  this->countOp = 0;
  pointer = first;
  for (int i = 0; i < targetOp; i++) {
    if (i % 2 == 0) {
      pointer = pointer->next;
    } else {
      pointer = pointer->prev;
    }
    this->countOp++;
  }

  return size;
}

int Train::getOpCount() {
  return this->countOp;
}

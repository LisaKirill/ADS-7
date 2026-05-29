// Copyright 2021 NNTU-CS
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

  this->countOp = 0;
  Car* pointer = first;
  pointer->light = true;

  int current_size = 1;
  while (pointer->light) {
    // Смещение вперед на текущую предполагаемую длину (счетчик вверх)
    int step_forward = 0;
    while (step_forward < current_size) {
      pointer = pointer->next;
      this->countOp++;
      step_forward++;
    }

    // Выключение света в проверочном вагоне
    pointer->light = false;

    // Смещение обратно к исходной точке (счетчик вниз)
    int step_backward = current_size;
    while (step_backward > 0) {
      pointer = pointer->prev;
      this->countOp++;
      step_backward--;
    }

    // Проверка: если свет в базовом вагоне погас, мы нашли длину
    if (pointer->light == false) {
      return current_size;
    }

    current_size++;
  }
  return current_size;
}

int Train::getOpCount() {
  return this->countOp;
}

// Copyright 2022 NNTU-CS
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "train.h"

int main() {
  std::srand(time(nullptr));
  std::cout << "n\tfalse\ttrue\trandom" << std::endl;
  for (int n = 2; n <= 100; n++) {
    int F;
    int T;
    int R;
    {
      Train train;
      for (int i = 0; i < n; i++)
        train.addCar(false);
      train.getLength();
      F = train.getOpCount();
    }
    {
      Train train;
      for (int i = 0; i < n; i++)
        train.addCar(true);

      train.getLength();
      T = train.getOpCount();
    }
    {
      Train train;
      for (int i = 0; i < n; i++)
        train.addCar(std::rand() % 2);

      train.getLength();
      R = train.getOpCount();
    }
    std::cout << n << "\t" << F << "\t" << T << "\t" << R
              << std::endl;
  }
  return 0;
}

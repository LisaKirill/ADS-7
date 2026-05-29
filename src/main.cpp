// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include "../include/train.h"

int main() {
  // Создаем папку через системный вызов и сохраняем результат, чтобы не было ошибок
#ifdef _WIN32
  int dir_res = std::system("mkdir result 2>nul");
#else
  int dir_res = std::system("mkdir -p result");
#endif

  if (dir_res == -1) {
    return 1;
  }

  std::ofstream dataFile("result/metrics.csv");
  if (!dataFile.is_open()) {
    return 1;
  }
  dataFile << "Length,AllOff,AllOn,Random\n";

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 1);

  for (int n = 10; n <= 400; n += 10) {
    Train trainOff;
    for (int i = 0; i < n; ++i) {
      trainOff.addCar(false);
    }
    trainOff.getLength();
    int opsOff = trainOff.getOpCount();

    Train trainOn;
    for (int i = 0; i < n; ++i) {
      trainOn.addCar(true);
    }
    trainOn.getLength();
    int opsOn = trainOn.getOpCount();

    Train trainRand;
    for (int i = 0; i < n; ++i) {
      trainRand.addCar(distrib(gen) == 1);
    }
    trainRand.getLength();
    int opsRand = trainRand.getOpCount();

    dataFile << n << "," << opsOff << "," << opsOn << "," << opsRand << "\n";
  }
  dataFile.close();

  std::ofstream scriptFile("result/build_plot.py");
  if (scriptFile.is_open()) {
    scriptFile << "import pandas as pd\n";
    scriptFile << "import matplotlib.pyplot as plt\n";
    scriptFile << "import numpy as np\n";
    scriptFile << "df = pd.read_csv('result/metrics.csv')\n";
    scriptFile << "n = df['Length']\n";
    scriptFile << "plt.figure(figsize=(10, 6))\n";
    scriptFile << "plt.scatter(n, df['AllOff'], color='blue', label='Off')\n";
    scriptFile << "plt.scatter(n, df['AllOn'], color='red', label='On')\n";
    scriptFile << "plt.scatter(n, df['Random'], color='green', label='Rand')\n";
    scriptFile << "def t(x, y, c):\n";
    scriptFile << "  z = np.polyfit(x, y, 2)\n";
    scriptFile << "  p = np.poly1d(z)\n";
    scriptFile << "  plt.plot(x, p(x), color=c, linestyle='--')\n";
    scriptFile << "t(n, df['AllOff'], 'blue')\n";
    scriptFile << "t(n, df['AllOn'], 'red')\n";
    scriptFile << "t(n, df['Random'], 'green')\n";
    scriptFile << "plt.grid(True)\n";
    scriptFile << "plt.savefig('result/plot.png')\n";
    scriptFile.close();
  }

  // Запускаем Python-скрипт и проверяем код возврата для удовлетворения -Werror
#ifdef _WIN32
  int plot_res = std::system("python result/build_plot.py");
#else
  int plot_res = std::system("python3 result/build_plot.py");
#endif

  if (plot_res == -1) {
    return 1;
  }

  return 0;
}

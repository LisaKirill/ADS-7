// Copyright 2022 NNTU-CS
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#include "train.h"

using namespace std;

static Train buildTrain(int n, int mode, mt19937& gen) {
    Train train;
    uniform_int_distribution<int> bit(0, 1);

    for (int i = 0; i < n; ++i) {
        bool light = false;

        if (mode == 0) {
            light = false;
        } else if (mode == 1) {
            light = true;
        } else {
            light = bit(gen);
        }

        train.addCar(light);
    }

    return train;
}

int main() {
    mt19937 gen(random_device{}());

    ofstream out("result/experiment.csv");
    out << "n,all_off,all_on,random\n";

    cout << setw(6) << "n"
         << setw(12) << "off"
         << setw(12) << "on"
         << setw(12) << "rand" << '\n';

    for (int n = 2; n <= 60; ++n) {
        Train tOff = buildTrain(n, 0, gen);
        tOff.getLength();
        int opOff = tOff.getOpCount();

        Train tOn = buildTrain(n, 1, gen);
        tOn.getLength();
        int opOn = tOn.getOpCount();

        long long sumRand = 0;
        const int trials = 50;
        for (int i = 0; i < trials; ++i) {
            Train tRand = buildTrain(n, 2, gen);
            tRand.getLength();
            sumRand += tRand.getOpCount();
        }
        int opRand = static_cast<int>(sumRand / trials);

        out << n << "," << opOff << "," << opOn << "," << opRand << "\n";

        cout << setw(6) << n
             << setw(12) << opOff
             << setw(12) << opOn
             << setw(12) << opRand << '\n';
    }

    return 0;
}

#ifndef STEP01_SIMULATEDANNEALING_H
#define STEP01_SIMULATEDANNEALING_H

#include "../utils/structures/Matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

static const auto STARTING_TEMP = exp(12);
static const double ENDING_TEMP = 0.1;
static const double TEMPERATURE_CHANGE_VALUE = 0.99;


class SimulatedAnnealing {
private:
    vector<vector<Details>> instance;
    int numberOfCities;

    vector<int> findRandomPermutation();
    vector<int> findAdjacentPermutation(vector<int> permutation);
    int calculateCost(vector<int> permutation);

public:
    explicit SimulatedAnnealing(Matrix matrix);

    vector<int> findPath();
};


#endif

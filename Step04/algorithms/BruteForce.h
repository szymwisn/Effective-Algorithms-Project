#ifndef STEP01_BRUTE_FORCE_H
#define STEP01_BRUTE_FORCE_H

#include "../utils/structures/Matrix.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


class BruteForce {
private:
    Matrix matrix;
    vector<int> cities;
    int numberOfCities;
    vector<vector<int>> permutations;

    vector<int> getAllCities();
    vector<vector<int>> getPermutations();
    int factorial(int n);

public:
    explicit BruteForce(Matrix matrix);

    vector<int> findPath();
};


#endif

#ifndef STEP01_DYNAMIC_PROGRAMMING_H
#define STEP01_DYNAMIC_PROGRAMMING_H

#include "../utils/structures/Matrix.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


class DynamicProgramming {
private:
    vector<vector<Details>> instance;
    int numberOfCities;
    int** cache;
    int** lastCities;
    vector<int> path;

    void execute();
    int execute(int city, int mask);
    bool hasTheCityBeenVisited(int city, int mask);
    void collectPaths();
    int calcNextMask(int city, int oldMask);
    void allocateMemory();
    void fillArrays();

public:
    explicit DynamicProgramming(Matrix matrix);

    vector<int> findPath();
};


#endif

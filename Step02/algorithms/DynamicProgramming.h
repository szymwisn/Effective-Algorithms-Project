#ifndef STEP01_DYNAMIC_PROGRAMMING_H
#define STEP01_DYNAMIC_PROGRAMMING_H

#include "../utils/structures/Matrix.h"
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


class DynamicProgramming {
private:
    vector<vector<Details>> instance;
    int cities;
    int firstCity;
    int** cache;
    int** lastCities;
    vector<int> path;

    void allocateMemory();
    void fillArrays();
    void execute();
    int execute(int city, int mask);
    bool isProcessingProperCity(int city, int mask);
    void collectPaths();
    int calcNextMask(int city, int oldMask);

public:
    explicit DynamicProgramming(int firstCity, Matrix matrix);

    vector<int> findPath();
};


#endif

#ifndef STEP01_DYNAMIC_PROGRAMMING_H
#define STEP01_DYNAMIC_PROGRAMMING_H

#include "../utils/structures/Matrix.h"
#include<bits/stdc++.h>
#include <iostream>

using namespace std;


class Dynamic_programming {
private:
    vector<vector<Details>> instance;
    int cities;
    int** cache;
    int** lastCities;
    vector<int> path;
    int firstCity;

    void allocateMemory();
    void fillArrays();
    void execute();
    int execute(int city, int mask);
    void collectPaths();
    int calcNextMask(int city, int oldMask);

public:
    explicit Dynamic_programming(int firstCity, Matrix matrix);

    vector<int> findPath();
};


#endif

#ifndef STEP01_MATRIX_H
#define STEP01_MATRIX_H

#include "Details.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class Matrix {
private:
    vector<vector<Details>> instance;
    int numberOfCities;

    void clear();
public:
    explicit Matrix();
    explicit Matrix(int numberOfCities);
    explicit Matrix(vector<vector<Details>> &instance);

    void setInstance(vector<vector<Details>> &instance);
    vector<vector<Details>> getInstance();

    void display();
    void generate(int numberOfCities);
    int calculateCostValue(vector<int>);
};


#endif

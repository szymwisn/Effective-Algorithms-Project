
#ifndef STEP01_GENETIC_H
#define STEP01_GENETIC_H

#include <iostream>
#include <vector>
#include "../utils/structures/Details.h"
#include "../utils/structures/Matrix.h"
#include <bits/stdc++.h>

using namespace std;


class Genetic {
private:
    int populationSize;
    int eliteSize;
    float mutationRate;
    int generations;

    vector<vector<Details>> instance;
    int numberOfCities;
    vector<int> path;
    vector<int> citiesList;
    vector<vector<int>> population;

    vector<pair<vector<int>, float>> chromosomeWithFitness;

    vector<int> getAllCities();
    vector<vector<int>> randomizePopulation();
    void rankChromosomes();
    pair<vector<int>, vector<int>> select();
    vector<int> crossover(pair<vector<int>, vector<int>> parents);
    vector<int> mutate (vector<int> child);
    float calculateFitness(vector<int> chromosome);
    float normalizeFitness(float fitness, float totalFitness);

public:
    explicit Genetic(Matrix matrix, int populationSize, int eliteSize, float mutationRate, int generations);

    vector<int> findPath();

};


#endif 

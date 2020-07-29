#ifndef STEP01_ANT_H
#define STEP01_ANT_H

#include <vector>
#include "../utils/structures/Details.h"
#include "../utils/structures/Matrix.h"
#include <stdint-gcc.h>
#include <cstdlib>
#include <math.h>

using namespace std;

class Ant {
public:
    int n;
    vector<bool> visited;

    Ant(int n, int cities) {
        this->n = n;
        this->visited.resize(cities, false);
    };
    ~Ant() {
        this->visited.clear();
    };
};

class AntColony {
private:
    vector<vector<Details>> instance;
    int numberOfCities;
    int iterations;
    double ro, alpha, beta;

    void definePathsForAnt(Ant *ant, vector<vector<int>> &paths, vector<vector<double>> &pheromones);
    double calcProbability(int firstCity, int secondCity, Ant *ant, vector<vector<double>> &pheromones);
    int getNextCity (vector<double> &probabilities);
    void evaporatePheromones(vector<vector<int>> &paths, vector<vector<double>> &pheromones);
    vector<int> defineBestPath(const vector<vector<int>> &paths);
    int calculateCost(vector<int> path);

public:
    explicit AntColony(Matrix matrix, int iterations, double ro, double alpha, double beta);

    vector<int> findPath();
};


#endif

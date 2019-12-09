#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(Matrix matrix) {
    this->instance = matrix.getInstance();
    this->numberOfCities = (int) this->instance.size();
}

vector<int> SimulatedAnnealing::findPath() {
    vector<int> bestPath = findRandomPermutation();
    double temperature = STARTING_TEMP;

    while(temperature > ENDING_TEMP) {
        int bestCost = calculateCost(bestPath);

        int iter = 0;
        while(iter++ < this->numberOfCities * 3) {
            vector<int> adjacentPath = findAdjacentPermutation(bestPath);
            int adjacentCost = calculateCost(adjacentPath);

            int costDifference = adjacentCost - bestCost;

            if(costDifference < 0 ||
               exp(-costDifference / temperature) > ((double) rand() / (RAND_MAX)) + 1) {
                bestPath = adjacentPath;
                break;
            }
        }

        temperature *= TEMPERATURE_CHANGE_VALUE;
    }

    return bestPath;
}

vector<int> SimulatedAnnealing::findRandomPermutation() {
    vector<int> permutation;
    vector<int> valuesLeft;

    permutation.reserve((unsigned long) this->numberOfCities);
    valuesLeft.reserve((unsigned long) this->numberOfCities);

    for(int i = 0; i < this->numberOfCities; i++) {
        valuesLeft.push_back(i);
    }

    for(int i = 0; i < this->numberOfCities; i++) {
        int index = rand() % (int) valuesLeft.size();
        permutation.push_back(valuesLeft[index]);
        valuesLeft.erase(valuesLeft.begin() + index);
    }

    return permutation;
}

vector<int> SimulatedAnnealing::findAdjacentPermutation(vector<int> permutation) {
    vector<int> newPermutation = permutation;
    int indexA, indexB;

    indexA = rand() % this->numberOfCities;

    do {
        indexB = rand() % this->numberOfCities;
    } while (indexB == indexA);

    newPermutation[indexA] = permutation[indexB];
    newPermutation[indexB] = permutation[indexA];

    return newPermutation;
}

int SimulatedAnnealing::calculateCost(vector<int> permutation) {
    int cost = 0;

    for(int i = 0; i < permutation.size() - 1; i++) {
        cost += this->instance[permutation[i]][permutation[i+1]].distance;
    }

    cost += this->instance[permutation[permutation.size() - 1]][permutation[0]].distance;

    return cost;
}

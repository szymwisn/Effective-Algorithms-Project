#include "BruteForce.h"

BruteForce::BruteForce(int firstCity, Matrix matrix) {
    this->matrix = matrix;
    this->firstCity = firstCity;
    this->numberOfCities = (int) matrix.getInstance().size();
    this->cities = getAllCities();
    this->permutations = getPermutations();
}

vector<int> BruteForce::findPath() {
    int minDistance = INT_MAX;
    vector<int> bestPermutation;

    for(const vector<int> &permutation : this->permutations) {
        int distance = this->matrix.calculateCostValue(permutation);
        if(distance < minDistance) {
            bestPermutation = permutation;
            minDistance = distance;
        }
    }

    return bestPermutation;
}

vector<int> BruteForce::getAllCities() {
    vector<int> citiesList;
    citiesList.resize((unsigned long) this->numberOfCities);

    for(int i = 0; i < citiesList.size(); i++) {
        citiesList[i] = i;
    }

    return citiesList;
}

vector<vector<int>> BruteForce::getPermutations() {
    vector<vector<int>> permutations;
    permutations.resize((unsigned long) factorial(this->numberOfCities));

    int k = 0;
    do {
        permutations[k] = this->cities;
        k++;
    } while (next_permutation(this->cities.begin(), this->cities.end()));

    return permutations;
}

int BruteForce::factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

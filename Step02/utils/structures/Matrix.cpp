#include "Matrix.h"

Matrix::Matrix() {
    vector<vector<Details>> instance;
    this->instance = instance;
    this->numberOfCities = (int) this->instance.size();
}

Matrix::Matrix(int numberOfCities) {
    generate(numberOfCities);
}

Matrix::Matrix(vector<vector<Details>> &instance) {
    this->instance = instance;
    this->numberOfCities = (int) this->instance.size();
}

void Matrix::setInstance(vector<vector<Details>> &instance) {
    this->instance = instance;
    this->numberOfCities = (int) this->instance.size();
}

vector<vector<Details>> Matrix::getInstance() {
    return this->instance;
}

void Matrix::display() {
    for(int i = 0; i < this->numberOfCities; i++) {
        for(int j = 0; j < this->numberOfCities; j++) {
            cout.width(3);
            cout << this->instance[i][j].distance << " ";
        }
        cout << endl;
    }
}

void Matrix::generate(int numberOfCities) {
    srand(time(nullptr));

    clear();
    this->numberOfCities = numberOfCities;
    vector<vector<Details>> instance;

    instance.resize((unsigned long long int) this->numberOfCities);
    for(int i = 0; i < this->numberOfCities; i++) {
        instance[i].resize((unsigned long long int) this->numberOfCities);
    }

    for(int i = 0; i < this->numberOfCities; i++) {
        for(int j = 0; j < this->numberOfCities; j++) {
            Details details;
            if(i != j ) {
                details.distance = rand() % 100 + 1;
            }
            instance[i][j] = details;
        }
    }

    this->instance = instance;
}

int Matrix::calculateCostValue() {
    int cost = 0;

    for(int i = 0; i < this->numberOfCities; i++) {
        for(int j = 0; j < this->numberOfCities; j++) {
            if(j == i + 1) {
                cost += this->instance[i][j].distance;
            }
        }
    }

    cost += this->instance[this->numberOfCities-1][0].distance;

    return cost;
}

int Matrix::calculateCostValue(vector<int> cities) {
    int cost = 0;

    for(int i = 0; i < cities.size() - 1; i++) {
        cost += this->instance[cities[i]][cities[i+1]].distance;
    }

    cost += this->instance[cities[cities.size() - 1]][cities[0]].distance;

    return cost;
}

void Matrix::clear() {
    this->numberOfCities = 0;
    this->instance.clear();
}

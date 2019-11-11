#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming(Matrix matrix) {
    this->instance = matrix.getInstance();
    this->numberOfCities = (int) this->instance.size();

    // allocate memory for arrays
    allocateMemory();

    // fill arrays with -1 value
    fillArrays();
}

vector<int> DynamicProgramming::findPath() {
    execute();
    collectPaths();
    return this->path;
}

void DynamicProgramming::execute() {
    // set city as firstCity
    int city = 0;

    // and calculate it's binary mask
    int mask = 1 << city;

    // execute the recursive algorithm
    execute(city, mask);
}

int DynamicProgramming::execute(int city, int mask) {
    int const VISITED_ALL_MASK = (1 << this->numberOfCities) - 1;
    int minDistance = INT_MAX;
    int lastCity = -1;

    // if each city has already been visited - go back to the first city
    if (mask == VISITED_ALL_MASK)
        return this->instance[city][0].distance;

    // if distance already in cache - return it's value
    if (this->cache[city][mask] != -1)
        return this->cache[city][mask];

    // for each city find all permutations and define the index of the last city
    for (int nextCity = 0; nextCity < this->numberOfCities; nextCity++) {
        // continue if processing the proper city
        if (isProcessingProperCity(nextCity, mask)) {
            // calculate the distance recursively
            int distance = this->instance[city][nextCity].distance + execute(nextCity, calcNextMask(nextCity, mask));

            // if a new minDistance found then set the city as the last one
            if (distance < minDistance) {
                minDistance = distance;
                lastCity = nextCity;
            }
        }
    }

    this->lastCities[city][mask] = lastCity;
    this->cache[city][mask] = minDistance;

    return minDistance;
}

bool DynamicProgramming::isProcessingProperCity(int city, int mask) {
    return (mask & (1 << city)) == 0;
}

void DynamicProgramming::collectPaths() {
    // set city as firstCity
    int city = 0;

    // and calculate it's binary mask
    int mask = 1 << city;

    for(int i = 0; i < numberOfCities; i++) {
        // add the city to the path vector
        this->path.push_back(city);

        // select the next city
        city = lastCities[city][mask];

        // if the last city was already found - stop collecting cities
        if (city == -1)
            break;

        // set the mask to the next city
        mask = calcNextMask(city, mask);
    }
}

int DynamicProgramming::calcNextMask(int city, int oldMask) {
    return oldMask | (1 << city);
}

void DynamicProgramming::allocateMemory() {
    // this->cities possible cities that could have been visited as the last ones and
    // 2^this->cities (1 << this -> cities) possible subsets of visited cities
    this->cache = new int*[this->numberOfCities];

    for(int i = 0; i < this->numberOfCities; i++) {
        this->cache[i] = new int[1 << this->numberOfCities];
    }

    this->lastCities = new int*[this->numberOfCities];

    for(int i = 0; i < this->numberOfCities; i++) {
        this->lastCities[i] = new int[1 << this->numberOfCities];
    }
}

void DynamicProgramming::fillArrays() {
    for(int i = 0; i < this->numberOfCities; i++) {
        for(int j = 0; j < 1 << this->numberOfCities; j++) {
            this->cache[i][j] = -1;
        }
    }

    for(int i = 0; i < this->numberOfCities; i++) {
        for(int j = 0; j < 1 << this->numberOfCities; j++) {
            this->lastCities[i][j] = -1;
        }
    }
}

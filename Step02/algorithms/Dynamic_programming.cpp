#include "Dynamic_programming.h"

Dynamic_programming::Dynamic_programming(int firstCity, Matrix matrix) {
    this->firstCity = firstCity;
    this->instance = matrix.getInstance();
    this->cities = (int) this->instance.size();

    // allocate memory for arrays
    allocateMemory();

    // fill arrays with -1 value
    fillArrays();

}

void Dynamic_programming::allocateMemory() {
    // this->cities possible cities that could have been visited as the last ones and
    // 2^this->cities (1 << this -> cities) possible subsets of visited cities
    cache = new int*[this->cities];

    for(int i = 0; i < this->cities; i++) {
        cache[i] = new int[1 << this->cities];
    }

    lastCities = new int*[this->cities];

    for(int i = 0; i < this->cities; i++) {
        lastCities[i] = new int[1 << this->cities];
    }
}

void Dynamic_programming::fillArrays() {
    for(int i = 0; i < this->cities; i++) {
        for(int j = 0; j < 1 << this->cities; j++) {
            this->cache[i][j] = -1;
        }
    }

    for(int i = 0; i < this->cities; i++) {
        for(int j = 0; j < 1 << this->cities; j++) {
            this->lastCities[i][j] = -1;
        }
    }
}

vector<int> Dynamic_programming::findPath() {
    execute();
    collectPaths();
    return this->path;
}

void Dynamic_programming::execute() {
    // set city as firstCity
    int city = this->firstCity;

    // and calculate it's binary mask
    int mask = 1 << city;

    // execute the recursive algorithm
    execute(city, mask);
}

int Dynamic_programming::execute(int city, int mask) {
    int minDistance = INT_MAX;
    int lastCity = -1;

    // if each city has already been visited - go back to the first city
    if (mask == (1 << this->cities) - 1)
        return this->instance[city][this->firstCity].distance;

    // if distance already in cache - return it's value
    if (this->cache[city][mask] != -1)
        return this->cache[city][mask];

    // for each city find all permutations and define the index of the last city
    for (int i = 0; i < this->cities; i++) {
        // continue if processing the proper city
        if ((mask & (1 << i)) == 0) {
            // set the new mask
            int nextMask = calcNextMask(i, mask);

            // calculate the distance for the permutation recursively
            int distance = this->instance[city][i].distance + execute(i, nextMask);

            // if a new minDistance found then set the city as the last one
            if (distance < minDistance) {
                minDistance = distance;
                lastCity = i;
            }
        }
    }

    this->lastCities[city][mask] = lastCity;
    this->cache[city][mask] = minDistance;

    return minDistance;
}

void Dynamic_programming::collectPaths() {
    // set city as firstCity
    int city = this->firstCity;

    // and calculate it's binary mask
    int mask = 1 << city;

    for(int i = 0; i < cities; i++) {
        // add the city to the path vector
        path.push_back(city);

        // select the next city
        city = lastCities[city][mask];

        // if the last city was already found - stop collecting cities
        if (city == -1)
            break;

        // set the mask to the next city
        mask = calcNextMask(city, mask);
    }
}

int Dynamic_programming::calcNextMask(int city, int oldMask) {
    return oldMask | (1 << city);
}

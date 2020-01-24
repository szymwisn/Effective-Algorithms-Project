#include "Genetic.h"

Genetic::Genetic(Matrix matrix, int populationSize, int eliteSize, float mutationRate, int generations) {
    this->populationSize = populationSize;
    this->eliteSize = eliteSize;
    this->mutationRate = mutationRate;
    this->generations = generations;
    this->instance = matrix.getInstance();
    this->numberOfCities = (int) this->instance.size();
    this->citiesList = this->getAllCities();
}

vector<int> Genetic::findPath() {
    int bestCost = INT32_MAX;
    vector<vector<int>> nextPopulation((unsigned long long) this->populationSize);

    for(int i = 0; i < nextPopulation.size(); i++) {
        nextPopulation.resize((unsigned long long) this->numberOfCities);
    }

    // find the initial population
    this->population = this->randomizePopulation();

    for(int i = 0; i < this->generations; i++) {
        while(nextPopulation.size() < this->population.size()) {
            // select two best parents parents
            pair<vector<int>, vector<int>> parents = select();

            // add values to mating pool
            vector<int> child = crossover(parents);

            // mutates the population
            vector<int> mutatedChild = mutate(child);

            nextPopulation.push_back(mutatedChild);
        }

        this->population = nextPopulation;

        for(const auto& path : this->population) {
            int cost = calculateCost(path);

            if(cost < bestCost) {
                bestCost = cost;
                this->bestPath = path;
            }
        }
    }

    return this->bestPath;
}

vector<int> Genetic::getAllCities() {
    vector<int> cities;
    cities.resize((unsigned long) this->numberOfCities);

    for(int i = 0; i < cities.size(); i++) {
        cities[i] = i;
    }

    return cities;
}

vector<vector<int>> Genetic::randomizePopulation() {
    vector<vector<int>> pop;
    pop.resize((unsigned long) this->populationSize);

    int k = 0;
    do {
        pop[k] = this->citiesList;
        k++;
    } while (next_permutation(this->citiesList.begin(), this->citiesList.end()) && k < this->populationSize);

    return pop;
}

bool sortByFitness(const pair<vector<int>, float> &a, const pair<vector<int>, float> &b) {
    return (a.second > b.second);
}

pair<vector<int>, vector<int>> Genetic::select() {
    float totalFitness= 0;

    // calculate fitness of each chromosome from the calculated population
    for(const auto& chromosome : this->population) {
        float fitness = this->calculateFitness(chromosome);
        totalFitness += fitness;
        chromosomeWithFitness.emplace_back(chromosome, fitness);
    }

    sort(chromosomeWithFitness.begin(), chromosomeWithFitness.end(), sortByFitness);

    pair<vector<int>, vector<int>> parents = make_pair(chromosomeWithFitness[0].first, chromosomeWithFitness[1].first);
    return parents;
}

float Genetic::calculateFitness(vector<int> chromosome) {
    int cost = 0;

    for(int i = 0; i < chromosome.size() - 1; i++) {
        cost += this->instance[chromosome[i]][chromosome[i + 1]].distance;
    }

    cost += this->instance[chromosome[chromosome.size() - 1]][chromosome[0]].distance;

    return 1 / (float) cost;
}

vector<int> Genetic::crossover(pair<vector<int>, vector<int>> parents) {
    int a, b;
    vector<int> parent1 = parents.first;
    vector<int> parent2 = parents.second;
    vector<int> child(parent1.size());

    a = rand() % this->numberOfCities;

    do {
        b = rand() % this->numberOfCities;
    } while(a == b);

    if (a > b) {
        swap(a, b);
    }

    // TODO finish

    return child;
}

// inversion
vector<int> Genetic::mutate(vector<int> child) {
    int lower, upper;

    lower = rand() % this->numberOfCities;

    do {
        upper = rand() % this->numberOfCities;
    } while (lower == upper);

    if(lower > upper) {
        swap(lower, upper);
    }

    for (int i = lower, j = upper; i < j; i++, j--) {
        swap(child[i], child[j]);
    }

    return child;
}

int Genetic::calculateCost(vector<int> path) {
    int cost = 0;

    for(int i = 0; i < path.size() - 1; i++) {
        cost += this->instance[path[i]][path[i + 1]].distance;
    }

    cost += this->instance[path[path.size() - 1]][path[0]].distance;

    return cost;
}

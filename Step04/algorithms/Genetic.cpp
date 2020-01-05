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

bool sortByFitness(const pair<vector<int>, float> &a, const pair<vector<int>, float> &b) {
    return (a.second > b.second);
}

vector<int> Genetic::findPath() {
    vector<vector<int>> nextPopulation;

    // find the initial population
    this->population = this->randomizePopulation();

//    for(int i = 0; i < this->generations; i++) {
//        while(nextPopulation.size() < this->population.size()) {
            // assign fitness to chromosomes
            rankChromosomes();

            // select two parents
            pair<vector<int>, vector<int>> parents = select();

            // add values to mating pool
            vector<int> child = crossover(parents);

            // mutates the population
            vector<int> mutatedChild = mutate(child);

            nextPopulation.push_back(mutatedChild);
//        }

//        this->population = nextPopulation;
//    }




    // sort chromosomes by fitness value - from best to worst
//    sort(chromosomeWithFitness.begin(), chromosomeWithFitness.end(), sortByFitness);

    // create a child element from two best parents
//    pair<vector<int>, vector<int>> parents = make_pair(chromosomeWithFitness[0].first, chromosomeWithFitness[1].first);


    for(const auto& pair : chromosomeWithFitness) {
        for( const auto& gene : pair.first) {
            cout << gene << " ";
        }
        cout << ", fitness: " << pair.second << endl;
    }


// TODO test

//    map<vector<int>, float> chromosomeWithFitnessMap;
//
//    for(int i = 0; i < this->populationSize; i++) {
//        float fitness = calculateFitness(this->population[i]);
//        chromosomeWithFitnessMap[this->population[i]] = fitness;
//    }
//
//    for(int i = 0; i < chromosomeWithFitnessMap.size(); i++) {
//        for(const auto& gene : this->population[i]) {
//            cout << gene << " ";
//        }
//        cout << ", fitness: " << chromosomeWithFitnessMap[this->population[i]] << endl;
//    }

    return vector<int>(1, 1);
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
    vector<vector<int>> p;
    p.resize((unsigned long) this->populationSize);

    int k = 0;
    do {
        p[k] = this->citiesList;
        k++;
    } while (next_permutation(this->citiesList.begin(), this->citiesList.end()) && k < this->populationSize);

    return p;
}

void Genetic::rankChromosomes() {
    float totalFitness= 0;// calculate fitness of each chromosome from the calculated population

    for(const auto& chromosome : this->population) {
        float fitness = this->calculateFitness(chromosome);
        totalFitness += fitness;
        chromosomeWithFitness.emplace_back(chromosome, fitness);
    }

    sort(chromosomeWithFitness.begin(), chromosomeWithFitness.end(), sortByFitness);

//    for(const auto& pair : chromosomeWithFitness) {
//        for( const auto& gene : pair.first) {
//            cout << gene << " ";
//        }
//        cout << ", fitness: " << pair.second << endl;
//    }

//    cout << endl << endl;

    // normalize fitness
    for (int i = 0; i < chromosomeWithFitness.size(); i++) {
        chromosomeWithFitness[i].second = this->normalizeFitness(chromosomeWithFitness[i].second, totalFitness);
    }
}

float Genetic::calculateFitness(vector<int> chromosome) {
    int cost = 0;

    for(int i = 0; i < chromosome.size() - 1; i++) {
        cost += this->instance[chromosome[i]][chromosome[i + 1]].distance;
    }

    cost += this->instance[chromosome[chromosome.size() - 1]][chromosome[0]].distance;

    return 1 / (float) cost;
}

float Genetic::normalizeFitness(float fitness, float totalFitness) {
    return (fitness/totalFitness) * 100;
}

pair<vector<int>, vector<int>> Genetic::select() {
    pair<vector<int>, vector<int>> parents = make_pair(chromosomeWithFitness[0].first, chromosomeWithFitness[1].first);
    return parents;
}

vector<int> Genetic::crossover(pair<vector<int>, vector<int>> parents) {
    return vector<int>();
}

vector<int> Genetic::mutate(vector<int> child) {
    return vector<int>();
}

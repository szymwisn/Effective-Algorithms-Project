#include "AntColony.h"

AntColony::AntColony(Matrix matrix, int iterations, double ro, double alpha, double beta) {
    this->instance = matrix.getInstance();
    this->numberOfCities = (int) this->instance.size();
    this->iterations = iterations;
    this->ro = ro;
    this->alpha = alpha;
    this->beta = beta;
}

vector<int> AntColony::findPath() {
    vector<vector<int>> antPaths((unsigned long) this->numberOfCities);
    vector<vector<double>> pheromones((unsigned long) this->numberOfCities);

    // resize vectors
    for(int i = 0; i < numberOfCities; i++) {
        antPaths[i].resize((unsigned long) numberOfCities, -1);
        pheromones[i].resize((unsigned long) numberOfCities);
    }

    // set initial pheromones values
    for(int i = 0; i < this->numberOfCities; i++) {
        for (int j = 0; j < this->numberOfCities; j++) {
            pheromones[i][j] = (double) rand() / RAND_MAX * this->numberOfCities / this->instance[0][1].distance;
        }
    }

    // in each iteration find paths for each ant and evaporate pheromones at the end
    for(int i = 0; i < this->iterations; i++) {
        // iterate over each city
        for(int j = 0; j < this->numberOfCities; j++) {
            // create new Ant for each city
            Ant *ant = new Ant(j, this->numberOfCities);

            // at first the ant has no cities on it's route
            for (int &city : antPaths[j]) {
                city = -1;
            }

            // and find it's routes
            definePathsForAnt(ant, antPaths, pheromones);
        }
        // at the end of each iteration evaporate pheromones
        evaporatePheromones(antPaths, pheromones);
    }

    // return best path found
    return defineBestPath(antPaths);
}

void AntColony::definePathsForAnt(Ant *ant, vector<vector<int>> &paths, vector<vector<double>> &pheromones) {
    vector<double> choiceProbabilities;

    // ant starts in the city of the same number
    paths[ant->n][0] = ant->n;

    // mark this city as visited
    ant->visited[ant->n] = true;

    // iterate over each city
    for (int i = 0; i < this->numberOfCities - 1; i++) {
        // first city
        int city = paths[ant->n][i];

        // clear probabilities
        choiceProbabilities.clear();
        choiceProbabilities.resize((unsigned long) this->numberOfCities, 0.0);

        // define probabilities of visiting next cities
        for (int secondCity = 0; secondCity < this->numberOfCities; secondCity++) {
            // if the city wasn't visited and isn't the same as the first city then calculate the probability of visiting the city
            if (city != secondCity && !ant->visited[secondCity]) {
                choiceProbabilities[secondCity] = calcProbability(city, secondCity, ant, pheromones);
            }
        }

        // get the next city based on probabilities
        paths[ant->n][i + 1] = getNextCity(choiceProbabilities);

        // mark the city as visited
        ant->visited[paths[ant->n][i + 1]] = true;
    }
}

// calculate probability of going to the next city based on pheromones using provided equations
double AntColony::calcProbability(int firstCity, int secondCity, Ant *ant, vector<vector<double>> &pheromones) {
    double tau_ij = pow(pheromones[firstCity][secondCity], this->alpha);
    double eta_ij = pow(1.0 / this->instance[firstCity][secondCity].distance, this->beta);

    double sum = 0;
    for (int city = 0; city < this->numberOfCities; city++) {
        // if the city wasn't visited and isn't the same as the first city then calculate the probability of visiting the city
        if(city != firstCity && !ant->visited[city]) {
            double tau_ic = pow(pheromones[firstCity][city], this->alpha);
            double eta_ic = pow(1.0 / this->instance[firstCity][city].distance, this->beta);
            sum += tau_ic * eta_ic;
        }
    }

    return (tau_ij * eta_ij) / (sum);
}

int AntColony::getNextCity(vector<double> &probabilities) {
    double threshold = (double) rand() / RAND_MAX;
    double sum = probabilities[0];

    int city = 0;
    while (sum < threshold){
        city++;
        sum += probabilities[city];
    }

    return city;
}

void AntColony::evaporatePheromones(vector<vector<int>> &paths, vector<vector<double>> &pheromones) {
    // iterate over paths
    for(int i = 0; i < paths.size(); i++) {
        int pathCost = calculateCost(paths[i]);

        // iterate over each path
        for(int j = 0; j < paths.size() - 1; j++) {
            int city = paths[i][j];
            int nextCity = paths[i][j + 1];

            pheromones[city][nextCity] = (1 - this->ro) * pheromones[city][nextCity] + this->numberOfCities / (double) pathCost;
            pheromones[nextCity][city] = (1 - this->ro) * pheromones[nextCity][city] + this->numberOfCities / (double) pathCost;
        }
    }
}

vector<int> AntColony::defineBestPath(const vector<vector<int>> &paths) {
    int best = INT32_MAX;
    vector<int> bestPath;

    for(int i = 0; i < this->numberOfCities; i++) {
        int route = calculateCost(paths[i]);

        if(route < best) {
            best = route;
            bestPath = paths[i];
        }
    }

    return bestPath;
}

int AntColony::calculateCost(vector<int> path) {
    int cost = 0;

    for(int i = 0; i < path.size() - 1; i++) {
        cost += this->instance[path[i]][path[i + 1]].distance;
    }

    cost += this->instance[path[path.size() - 1]][path[0]].distance;

    return cost;
}

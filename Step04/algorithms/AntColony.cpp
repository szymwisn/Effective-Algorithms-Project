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
    vector<vector<int>> paths((unsigned long) this->numberOfCities);
    vector<vector<double>> pheromones((unsigned long) this->numberOfCities);

    for(int i = 0; i < numberOfCities; i++) {
        paths[i].resize((unsigned long) numberOfCities, -1);
        pheromones[i].resize((unsigned long) numberOfCities);
    }

    for(int i = 0; i < this->numberOfCities; i++) {
        for (int j = 0; j < this->numberOfCities; j++) {
            pheromones[i][j] = (double) rand() / RAND_MAX * this->numberOfCities / this->instance[0][1].distance;
        }
    }

    for(int i = 0; i < this->iterations; i++) {
        for(int j = 0; j < this->numberOfCities; j++) {
            for (int &city : paths[j]) {
                city = -1;
            }

            Ant *ant = new Ant(j, this->numberOfCities);
            defineAntRoutes(ant, paths, pheromones);
        }
    }

    evaporatePheromones(pheromones, paths);

    return defineBestPath(paths);
}

void AntColony::defineAntRoutes(Ant *ant, vector<vector<int>> &routes, vector<vector<double>> &pheromones) {
    vector<double> probabilities;

    routes[ant->n][0] = ant->n;
    ant->visited[ant->n] = true;

    for (int i = 0; i < this->numberOfCities - 1; i++) {
        int city = routes[ant->n][i];

        probabilities.clear();
        probabilities.resize((unsigned long) this->numberOfCities, 0.0);

        for (int secondCity = 0; secondCity < this->numberOfCities; secondCity++) {
            if (city != secondCity && !ant->visited[secondCity]) {
                probabilities[secondCity] = calcPhiValue(city, secondCity, ant, pheromones);
            }
        }

        routes[ant->n][i + 1] = getNextCity(probabilities);
        ant->visited[routes[ant->n][i + 1]] = true;
    }
}

double AntColony::calcPhiValue(int firstCity, int secondCity, Ant *ant, vector<vector<double>> &pheromones) {
    double tau_ij = pow(pheromones[firstCity][secondCity], this->alpha);
    double eta_ij = pow(1.0 / this->instance[firstCity][secondCity].distance, this->beta);

    double sum = 0;
    for (int city = 0; city < this->numberOfCities; city++) {
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

void AntColony::evaporatePheromones(vector<vector<double>> &pheromones, vector<vector<int>> &routes) {
    for(int i = 0; i < routes.size(); i++) {
        int route_i = calculateCost(routes[i]);

        for(int j = 0; j < routes.size() - 1; j++) {
            int city = routes[i][j];
            int nextCity = routes[i][j + 1];

            pheromones[city][nextCity] = (1 - this->ro) * pheromones[city][nextCity] + this->numberOfCities / (double) route_i;
            pheromones[nextCity][city] = (1 - this->ro) * pheromones[nextCity][city] + this->numberOfCities / (double) route_i;
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

#include "FileManager.h"

Matrix FileManager::loadFromFile(string fileName) {
    ifstream file;
    string name;
    int numberOfCities;
    vector<vector<Details>> instance;
    vector<int> distances;

    file.open(fileName);

    if(file.is_open()) {
        string value;

        file >> value;
        name = value;

        file >> value;
        numberOfCities = stoi(value);

        while(file >> value) {
            distances.push_back(stoi(value));
        }
    } else {
        throw ios::failure("Failed opening file");
    }

    instance.resize((unsigned long long int) numberOfCities);
    for(int i = 0; i < numberOfCities; i++) {
        instance[i].resize((unsigned long long int) numberOfCities);
    }

    int k = 0;
    for(int i = 0; i < numberOfCities; i++) {
        for(int j = 0; j < numberOfCities; j++) {
            instance[i][j].distance = distances[k];
            k++;
        }
    }

    file.close();
    Matrix matrix(instance);

    return matrix;
}

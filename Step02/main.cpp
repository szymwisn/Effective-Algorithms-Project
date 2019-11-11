#include "utils/file manager/FileManager.h"
#include "algorithms/DynamicProgramming.h"
#include "algorithms/BruteForce.h"
#include <iostream>

void showMenu();
void printPathDetails(Matrix &matrix, const vector<int> &path);

using namespace std;


int main() {
    Matrix matrix;
    char option;

    cout << "--=== Traveling Salesman Problem ===--" << endl;

    do {
        showMenu();
        cin >> option;

        switch (option) {
            case '1': {
                string fileName;

                cout << "Enter file name >>";
                cin >> fileName;
                matrix.clear();
                matrix = FileManager::loadFromFile(fileName);
                matrix.display();
                break;
            }
            case '2': {
                int numberOfCities;

                cout << "Enter number of cities >>";
                cin >> numberOfCities;
                matrix.generate(numberOfCities);
                matrix.display();
                break;
            }
            case '3': {
                int distance;
                int numberOfCities;
                vector<vector<Details>> instance;

                cout << "Enter number of cities >>";
                cin >> numberOfCities;

                instance.resize((unsigned long long int) numberOfCities);
                for (int i = 0; i < numberOfCities; i++) {
                    instance[i].resize((unsigned long long int) numberOfCities);
                }

                for (int i = 0; i < numberOfCities; i++) {
                    for (int j = 0; j < numberOfCities; j++) {
                        if (i == j) {
                            instance[i][j].distance = -1;
                        } else {
                            cout << "Distance between city[" << i << "] and city[" << j << "]: " << endl;
                            cin >> distance;
                            instance[i][j].distance = distance;
                        }
                    }
                }

                matrix.clear();
                matrix.setInstance(instance);
                matrix.display();
                break;
            }
            case '4': {
                BruteForce bf(matrix);
                vector<int> path = bf.findPath();

                printPathDetails(matrix, path);

                break;
            }
            case '5': {
                DynamicProgramming dp(matrix);
                vector<int> path = dp.findPath();

                printPathDetails(matrix, path);

                break;
            }
            case 'q':
                cout << "--=== Application Closed ===--" << endl;
                break;
            default:
                cout << "[Error] Pressed Wrong Key" << endl;
                cout << "Available Options: " << endl;
                break;
        }
    } while (option != 'q');

    return 0;
}

void showMenu() {
    cout << "1 - Load Matrix From File" << endl;
    cout << "2 - Generate Random Matrix" << endl;
    cout << "3 - Create Matrix Manually" << endl;
    cout << "4 - TSP - brute force" << endl;
    cout << "5 - TSP - dynamic programming" << endl;
    cout << "q - Exit" << endl;
    cout << "Enter Key >> ";
}

void printPathDetails(Matrix &matrix, const vector<int> &path) {
    cout << "Cost Function Value of cities in order\n[";
    for(int city : path) {
        cout << city << " -> ";
    }

    cout << path[0] << "]\nis: ";
    cout << matrix.calculateCostValue(path) << endl;
}

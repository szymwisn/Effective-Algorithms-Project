#include "utils/file manager/FileManager.h"
#include "algorithms/DynamicProgramming.h"
#include "algorithms/BruteForce.h"
#include <iostream>
#include <chrono>

void showMenu();
void printPathDetails(Matrix &matrix, const vector<int> &path, long long time);

using namespace std;


int main() {
    static const int n = 1;
    static Matrix matrix;
    static char option;

    cout << "--=== Traveling Salesman Problem ===--" << endl;
    cout << "[ Measurements will be repeated " << n << " times ]"  << endl;

    do {
        showMenu();
        cin >> option;

        switch (option) {
            case '1': {
                string fileName;

                cout << "Enter file name >>";
                cin >> fileName;

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

                matrix.setInstance(instance);
                matrix.display();
                break;
            }
            case '4': {
                vector<int> path;
                long long timeSum = 0;

                for(int i = 0; i < n; i++) {
                    BruteForce bf(matrix);
                    auto start = chrono::steady_clock::now();
                    path = bf.findPath();
                    auto end = chrono::steady_clock::now();
                    timeSum += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                }

                printPathDetails(matrix, path, timeSum / n);

                break;
            }
            case '5': {
                vector<int> path;
                long long timeSum = 0;

                for(int i = 0; i < n; i++) {
                    DynamicProgramming dp(matrix);
                    auto start = chrono::steady_clock::now();
                    path = dp.findPath();
                    auto end = chrono::steady_clock::now();
                    timeSum += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                }

                printPathDetails(matrix, path, timeSum / n);
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
    cout << endl;
    cout << "1 - Load Matrix From File" << endl;
    cout << "2 - Generate Random Matrix" << endl;
    cout << "3 - Create Matrix Manually" << endl;
    cout << "4 - TSP - brute force" << endl;
    cout << "5 - TSP - dynamic programming" << endl;
    cout << "q - Exit" << endl;
    cout << "Enter Key >> ";
}

void printPathDetails(Matrix &matrix, const vector<int> &path, long long time) {
    cout << "Cost Value: ";
    cout << matrix.calculateCostValue(path) << endl;

    cout << "Path: [";
    for(int city : path) {
        cout << city << " -> ";
    }

    cout << path[0] << "]\n";

    cout << "Average time [ns]: " << time  << endl;
}

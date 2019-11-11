#include "utils/file manager/FileManager.h"
#include "algorithms/Dynamic_programming.h"
#include <iostream>

using namespace std;


int main() {
    static Matrix matrix;
    static char option;
    static string fileName;
    static int numberOfCities;
    static int distance;

    cout << "--=== Traveling Salesman Problem ===--" << endl;

    do {
        cout << "1 - Load Matrix From File" << endl;
        cout << "2 - Generate Random Matrix" << endl;
        cout << "3 - Create Matrix Manually" << endl;
        cout << "4 - TSP - dynamic programming" << endl;
        cout << "q - Exit" << endl;
        cout << "Enter Key >> ";
        cin >> option;

        switch (option) {
            case '1':
                cout << "Enter file name >>";
                cin >> fileName;
                matrix.clear();
                matrix = FileManager::loadFromFile(fileName);
                matrix.display();
                break;
            case '2':
                cout << "Enter number of cities >>";
                cin >> numberOfCities;
                matrix.generate(numberOfCities);
                matrix.display();
                break;
            case '3': {
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
                Dynamic_programming dp(1, matrix);
                vector<int> path = dp.findPath();

                cout << "Cost Function Value of cities in order\n[";
                for(int i = 0; i < path.size(); i++) {
                    cout << path[i] << " -> ";
                }

                cout << path[0] << "]\nis: ";
                cout << matrix.calculateCostValue(path) << endl;

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

#include "utils/file manager/FileManager.h"
#include <iostream>

using namespace std;


int main() {
    char option;
    string fileName;
    int numberOfCities;
    Matrix matrix;

    cout << "--=== Traveling Salesman Problem ===--" << endl;

    do {
        cout << "1 - Load Matrix From File" << endl;
        cout << "2 - Generate Random Matrix" << endl;
        cout << "3 - Calculate Cost Function" << endl;
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
            case '3':
                cout << "Cost Function Value: " << matrix.calculateCostValue() << endl;
                break;
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

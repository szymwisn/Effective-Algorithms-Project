#ifndef STEP01_FILE_H
#define STEP01_FILE_H

#include "../structures/Matrix.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;


class FileManager {
public:
    static Matrix loadFromFile(string fileName);
};


#endif

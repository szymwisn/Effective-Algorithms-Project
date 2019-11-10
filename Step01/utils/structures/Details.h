#ifndef STEP01_EDGE_H
#define STEP01_EDGE_H


struct Details {
    int distance;

    explicit Details(int distance = -1, bool visited = false) {
        this->distance = distance;
    }
};


#endif

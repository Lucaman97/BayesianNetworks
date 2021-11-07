//
// Created by lmann on 29/10/2021.
//

#ifndef PROGETTO_CPTABLE_H
#define PROGETTO_CPTABLE_H

#include <vector>

class CPTable {
public:
    CPTable();

//Eliminare il costruttore in base a quello che si decide di utilizzare
    std::vector<std::vector<float>> getTable();

private:
    std::vector<std::vector<float>> table;
};


#endif //PROGETTO_CPTABLE_H

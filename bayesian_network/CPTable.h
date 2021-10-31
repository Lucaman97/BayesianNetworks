//
// Created by lmann on 29/10/2021.
//

#ifndef PROGETTO_CPTABLE_H
#define PROGETTO_CPTABLE_H

#include <vector>

class CPTable {
public:
    //Eliminare il costruttore in base a quello che si decide di utilizzare
    CPTable(const std::string& gino);
    std::vector<std::vector<float>> getTable();

private:
    std::vector<std::vector<float>> table;
};


#endif //PROGETTO_CPTABLE_H

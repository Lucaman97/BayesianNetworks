//
// Created by lmann on 29/10/2021.
//

#ifndef PROGETTO_CPTABLE_H
#define PROGETTO_CPTABLE_H

#include <vector>

/*
 *
 * La cpTable avrà m^(n+1) elementi, con m che è il numero di state (present, absent) e
 * n che è il numero di parents.
*/
 class CPTable {
public:
    CPTable();

//Eliminare il costruttore in base a quello che si decide di utilizzare
    std::vector<std::vector<float>> getTable();

private:
    std::vector<std::vector<float>> table;
};


#endif //PROGETTO_CPTABLE_H

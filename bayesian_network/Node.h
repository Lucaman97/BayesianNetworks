#ifndef PROGETTO_NODE_H
#define PROGETTO_NODE_H

#include <iostream>
#include <utility>
#include "CPTable.h"

// this class will contain a CPT
class Node {
public:
    Node(std::string name) : name(std::move(name)) {};
    std::string getName() const;
    std::string getTable();
private:
    std::string name;
    CPTable table;
};


#endif //PROGETTO_NODE_H

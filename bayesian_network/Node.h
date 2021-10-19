#ifndef PROGETTO_NODE_H
#define PROGETTO_NODE_H

#include <iostream>
#include <utility>

// this class will contain a CPT
class Node {
public:
    explicit Node(std::string name) : name(std::move(name)) {};
    std::string getName() const;
private:
    std::string name;
};


#endif //PROGETTO_NODE_H

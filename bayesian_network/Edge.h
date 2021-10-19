#ifndef PROGETTO_EDGE_H
#define PROGETTO_EDGE_H

#include <iostream>
#include <utility>

class Edge {
public:
    Edge(std::string  from, std::string  to) : from(std::move(from)), to(std::move(to)) {};
private:
    std::string from;
    std::string to;
};


#endif //PROGETTO_EDGE_H

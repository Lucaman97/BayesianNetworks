#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Node.h"

class Graph {
public:
    void create_node(const std::string& name); // it will also need the probabilities
    void create_edge(const std::string& from, const std::string& to);
    // capire perché serve friend se la funzione è dentro la classe
    friend std::ostream& operator<<(std::ostream& out, const Graph& graph);
private:
    //unordered_map = tabella_hash
    std::unordered_map<std::string, std::vector<std::shared_ptr<Node>>> adj_list;
};


#endif //PROGETTO_GRAPH_H

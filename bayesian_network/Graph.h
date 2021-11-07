#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <iostream>
#include <vector> //mettere <set> al posto di <vector>
#include <unordered_map>
#include <memory>
#include "Node.h"
/*
 * Struttura dati per rappresentare il grafo:
A->C<-B

|Key|value|
|A   |[A,C]  |
|B   |[B,C]  |
|C   |[C]     |
 */


class Graph {
public:

    void create_node(const std::string& name); // it will also need the probabilities
    void create_edge(const std::string& from, const std::string& to);
    // perché serve friend se la funzione è dentro la classe?
    friend std::ostream& operator<<(std::ostream& out, const Graph& graph);
    Graph(const std::string& xdsl);
private:
    //unordered_map = tabella_hash
    //
    std::unordered_map<std::string, std::vector<std::shared_ptr<Node>>> adj_list;
    std::vector<std::string> tokenize(std::string const &str, const char delim);
};


#endif //PROGETTO_GRAPH_H

#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <random>
#include "Node.h"
#include "tinyxml2.h"

class Graph {
public:
    explicit Graph(const std::string& filename);
    //void create_node(const std::string& name, const std::shared_ptr<Node>& cpt); // it will also need the probabilities
    //void create_edge(const std::string& from, const std::string& to);
    std::shared_ptr<Node> getNode(const std::string& name);
    //friend std::ostream& operator<<(std::ostream& out, const Graph& graph);

    std::unordered_map<std::string,std::string> prior_sample();
    std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);
    std::vector<float> rejection_sampling(const std::string& query, int num_samples);
    std::vector<float> likelihood_weighting(const std::string& query, int num_samples);
    static std::unordered_map<std::string, std::vector<std::vector<float>>> probs_hashmap;
private:
    //unordered_map = tabella_hash
    //std::unordered_map<std::string, std::vector<std::shared_ptr<Node>>> adj_list;
    std::vector<std::shared_ptr<Node>> cpt_list;
    std::unordered_map<std::string,int> cpt_indexes;
    std::default_random_engine gen; // random number generator
};


#endif //PROGETTO_GRAPH_H

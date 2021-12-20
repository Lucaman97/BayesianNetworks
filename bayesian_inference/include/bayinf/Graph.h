#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <random>
#include "../../src/Node.h"
#include "../../src/COWBase.h"

namespace bayinf {

    class Graph {
    public:
        explicit Graph(const std::string& filename);
        //friend std::ostream& operator<<(std::ostream& out, const Graph& graph);

        std::vector<float> rejection_sampling(const std::string& query, int num_samples);
        std::vector<float> likelihood_weighting(const std::string& query, int num_samples);

    private:
        //methods
        std::shared_ptr<Node> getNode(const std::string& name);
        std::unordered_map<std::string,std::string> prior_sample();
        std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);
        //unordered_map = tabella_hash
        //std::unordered_map<std::string, std::vector<std::shared_ptr<Node>>> adj_list;

        //attributes
        std::vector<std::shared_ptr<Node>> cpt_list;
        std::unordered_map<std::string,int> cpt_indexes;
        std::default_random_engine gen; // random number generator
    };

}

#endif //PROGETTO_GRAPH_H

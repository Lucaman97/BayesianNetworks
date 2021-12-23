#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <random>
#include "../../src/Node.h"

namespace bayinf {

    class Graph {
    public:
        explicit Graph(const std::string& filename);
        //friend std::ostream& operator<<(std::ostream& out, const Graph& graph);
        void edit_cpt(const std::string& name, const std::string& problist); // problist is a list of probabilities separeted by a space
        std::vector<float> rejection_sampling(const std::string& query, int num_samples);
        std::vector<float> likelihood_weighting(const std::string& query, int num_samples);
        //void test(); // debug only
        std::vector<Node> node_list; // da rimettere private
    private:
        std::unordered_map<std::string,std::string> prior_sample();
        std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);

        std::unordered_map<std::string,int> node_indexes;
        std::default_random_engine gen; // random number generator
    };

}

#endif //PROGETTO_GRAPH_H

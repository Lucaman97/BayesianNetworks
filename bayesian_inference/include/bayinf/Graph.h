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

        std::vector<Node> node_list;
        void printNode(std::string name);
        inline int getMapSize(){ return Node::probs_hashmap.size();};
        inline void printMap() {
            for (auto& e : Node::probs_hashmap) {
                std::cout<<"\nCPT count: "<<e.second.use_count()<<std::endl;
                for (auto& row : *e.second) {
                    std::cout<<"Row: ";
                    for (auto& el : row) {
                        std::cout << el << " ";
                    }
                    std::cout<<std::endl;
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    private:
        std::unordered_map<std::string,std::string> prior_sample();
        std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);


        std::unordered_map<std::string,int> node_indexes;
        std::default_random_engine gen; // random number generator
    };

}

#endif //PROGETTO_GRAPH_H

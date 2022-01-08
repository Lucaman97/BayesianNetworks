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

        std::vector<Node> node_list;
        explicit Graph(const std::string& filename);

        // problist is a list of probabilities separated by a space
        void edit_cpt(const std::string& name, const std::string& problist);
        inline int getMapSize(){ return Node::probs_hashmap.size();};
        void printNode(const std::string& name);
        inline void printMap() {
            std::cout<< "----------HashMap----------";
            for (auto& e : Node::probs_hashmap) {
                std::cout<<"\nCPT count: "<<e.second.use_count()<<std::endl;
                for (auto& row : *e.second) {
                    for (auto& el : row) {
                        std::cout << el << " ";
                    }
                    std::cout<<std::endl;
                }
            }
            std::cout << "-------------------------"<<std::endl;
        }

        std::unordered_map<std::string, std::vector<float>> inference(int num_samples=1000, const std::string& evidence="", int algorithm=0);

        static void pretty_print(const std::unordered_map<std::string, std::vector<float>>& map);
        std::unordered_map<std::string,std::string> prior_sample();


        std::unordered_map<std::string,int> node_indexes;
    private:

        std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);
        std::vector<float> rejection_sampling(const std::string& query, int num_samples);
        std::vector<float> likelihood_weighting(const std::string& query, int num_samples);
        std::vector<float> forward_sampling(const std::string &query, int num_samples);
        int checkQueryValidity(const std::string&);

        std::default_random_engine gen; // random number generator
    };

}

#endif //PROGETTO_GRAPH_H

#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <random>
#include "../../src/Node.h"

#define DEBUG 0

namespace bayinf {

    class Graph {
    public:

        std::vector<Node> node_list;
        explicit Graph(const std::string& filename);
        //friend std::ostream& operator<<(std::ostream& out, const Graph& graph);
        void edit_cpt(const std::string& name, const std::string& problist); // problist is a list of probabilities separated by a space
        /*
        inline void test() {

           if (DEBUG == 0) {// debug only
               for (auto &node: node_list) {
                   std::cout << node.getName() << "\n";
                   for (auto &row: node.getProbabilities()) {
                       for (auto &el: row) {
                           std::cout << el << " ";
                       }
                       std::cout << "\n";
                   }
                   std::cout << "\n";
               };
           }


       }
        */
        void printNode(std::string name);
        inline int getMapSize(){ return Node::probs_hashmap.size();};
        inline void printMap() {
            for (auto& e : Node::probs_hashmap) {
                std::cout<<"\nCPT count: "<<e.second.use_count()<<std::endl;
                for (auto& row : *e.second) {
                    for (auto& el : row) {
                        std::cout << el << " ";
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }

        std::unordered_map<std::string, std::vector<float>> inference(int num_samples=1000, const std::string& evidence="", int algorithm=0);

        static void pretty_print(const std::unordered_map<std::string, std::vector<float>>& map);
        std::unordered_map<std::string,std::string> prior_sample();

    protected:
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

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
        std::vector<float> rejection_sampling(const std::string& query, int num_samples);
        std::vector<float> likelihood_weighting(const std::string& query, int num_samples);

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
    protected:
        std::unordered_map<std::string,int> node_indexes;
    private:
        std::unordered_map<std::string,std::string> prior_sample();
        std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);


        int checkQueryValidity(std::string);
        std::default_random_engine gen; // random number generator
    };

}

#endif //PROGETTO_GRAPH_H

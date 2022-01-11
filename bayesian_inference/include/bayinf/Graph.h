#ifndef PROGETTO_GRAPH_H
#define PROGETTO_GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <random>
#include "../../src/Node.h"

namespace baynet {


    /*
     * Class that models the graph of a Bayesian network.
     * The construction of the object takes place by indicating an .xdsl file as input
     */

    class Graph {
    public:

        //constructor: it takes the file path as input
        explicit Graph(const std::string& filename);

        //given the name of the node and a probabilities list it edits an existing node' cpt
        void edit_cpt(const std::string& name, const std::string& problist);

        //return the probs_hashmap size
        inline int get_map_size(){ return Node::probs_hashmap.size();};

        //given the name of the node, it prints:
        //name, parents, states, hashed cpt, cpt counter of that node
        void print_node(const std::string& name);

        //prints the whole probs_hashmap
        inline void print_map() {
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

        //given a number of samples and an evidence it performs inference using one of the implemented algorithms.
        //you can choose which algorithm to use with an integer
        std::unordered_map<std::string, std::vector<float>> inference(int num_samples=1000, const std::string& evidence="", int algorithm=0);

        //function to print the probabilities of a all nodes given the evidence: query = posterior|evidence
        //best to use with Graph::inference
        static void pretty_print(const std::unordered_map<std::string, std::vector<float>>& map);

        //function to print the probabilities of a single node given the evidence: query = posterior|evidence
        //best to use with Graph::inference
        static void pretty_print_query(std::unordered_map<std::string, std::vector<float>> results, std::string query);




        std::vector<Node> node_list;                        //ordered vector of nodes
        std::unordered_map<std::string,int> node_indexes;   //given the node name it returns the index for node_list
    private:

        std::unordered_map<std::string,std::string> prior_sample();
        std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);
        std::vector<float> rejection_sampling(const std::string& query, int num_samples);
        std::vector<float> likelihood_weighting(const std::string& query, int num_samples);
        std::vector<float> forward_sampling(const std::string &query, int num_samples);
        int check_query_validity(const std::string& s);

        std::default_random_engine gen; // random number generator
    };

}

#endif //PROGETTO_GRAPH_H

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

        //constructor: it takes the file path as input
        explicit Graph(const std::string& filename);

        //given the name of the node and a probabilities list it edits an existing node' cpt
        void edit_cpt(const std::string& name, const std::string& problist);

        //return the probs_hashmap size
        size_t getMapSize();

        //given the name of the node, it prints:
        //name, parents, states, hashed cpt, cpt counter of that node
        void printNode(const std::string& name);

        //prints the whole probs_hashmap
        void printMap();

        //given a number of samples and an evidence it performs inference using one of the implemented algorithms.
        //you can choose which algorithm to use with an integer:
        //      0: likelihood weighting (default)
        //      1: rejection sampling
        std::unordered_map<std::string, std::vector<float>> inference(int num_samples=1000, const std::string& evidence="", int algorithm=0);

        //function to print the probabilities of a all nodes given the evidence: query = posterior|evidence
        //best to use with Graph::inference
        static void pretty_print(const std::unordered_map<std::string, std::vector<float>>& map);

        //function to print the probabilities of a single node given the evidence: query = posterior|evidence
        //best to use with Graph::inference
        static void pretty_print_query(std::unordered_map<std::string, std::vector<float>> results, const std::string& query);

        // list of all the network nodes in topological order
        std::vector<Node> node_list;

        // given the node name it returns the index for node_list
        std::unordered_map<std::string,int> node_indexes;

    private:
        /*
         *  Generates a random state for a node according to its probability distribution.
         *  Return the name of the state
         */
        std::string generate_sample(const std::vector<float>& cond_probs, const std::vector<std::string>& states);

        /*
         *  Generates a sample from the network.
         *  Each variable is sampled according to the conditional distribution given the values already sampled for the parents
         *  Returns a map where the key is the variable name, and the value is the sampled state of the variable
         */
        std::unordered_map<std::string,std::string> prior_sample();

        /*
         *  Generates a sample from the network.
         *  Each non-evidence variable is sampled according to the conditional distribution given the values already sampled for the parents
         *  Returns a map where the key is the variable name, and the value is the sampled state of the variable
         *  Returns a weight representing the likelihood that the event accords to the evidence
         */
        std::tuple<std::unordered_map<std::string,std::string>, float> weighted_sample(const std::unordered_map<std::string, std::string>& evidence);

        /*
         * Performs approximate inference on a query variable using the rejection sampling algorithm
         * Returns a vector containing the conditional probabilities of the query variable
         */
        std::vector<float> rejection_sampling(const std::string& query, int num_samples);

        /*
        * Performs approximate inference on a query variable using the likelihood weighting algorithm
        * Returns a vector containing the conditional probabilities of the query variable
        */
        std::vector<float> likelihood_weighting(const std::string& query, int num_samples);

        // Estimates prior probability of each variable in the network (so without any evidence set) by generating num_samples events
        std::vector<float> forward_sampling(const std::string &query, int num_samples);

        int checkQueryValidity(const std::string&);

        std::default_random_engine gen; // random number generator
    };

}

#endif //PROGETTO_GRAPH_H

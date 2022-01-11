#ifndef PROGETTO_NODE_H
#define PROGETTO_NODE_H
#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <memory>
#include "COWBase.h"

class Node : public COWBase<std::vector<std::vector<float>>>{
public:
    //constructor
    explicit inline Node(std::string name, std::vector<std::string> states, std::unordered_map<std::string, int> states_map,
                  std::shared_ptr<std::vector<std::vector<float>>> probabilities, std::vector<std::string> parents,
                  std::string hashedCPT, std::vector<unsigned int> parent_wstates)

            : name(std::move(name)), states(std::move(states)), states_map(std::move(states_map)),
            parents(std::move(parents)), hashedCPT(std::move(hashedCPT)), parent_wstates(std::move(parent_wstates))
            {this->m_ptr=std::move((probabilities));};

    //returns node's name
    std::string get_name() const;

    //given a string it returns the sha1 hash of the string.
    static std::string hash_fun(const std::string& h);

    //return states_map
    std::unordered_map<std::string, int> get_states_map() const;

    //return states
    std::vector<std::string> get_states() const;

    //given a key it set the probability for the node
    void set_probabilities(const std::shared_ptr<std::vector<std::vector<float>>>& probabilities, const std::string& hashedCpt);

    //returns the parents
    std::vector<std::string> get_parents() const;

    //return the key for the probs_hashmap
    std::string get_hashed_cpt() const;

    //given an hashed cpt (a key of probs_hashmap) it checks if the reference counter is equal to 1.
    //if it is, the cpt is deleted
    static void probs_check_delete(const std::string& hashedCPT);

    std::vector<unsigned int> get_parent_weight_states() const;

    static std::unordered_map<std::string, std::shared_ptr<std::vector<std::vector<float>>>> probs_hashmap;
private:

    std::string name;
    std::unordered_map<std::string,int> states_map; // state,index
    std::vector<std::string> states;
    std::vector<std::string> parents;
    std::string hashedCPT;
    std::vector<unsigned int> parent_wstates; // useful for sampling
};


#endif //PROGETTO_NODE_H

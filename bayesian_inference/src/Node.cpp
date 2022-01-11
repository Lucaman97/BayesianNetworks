#ifndef BAYESIANNETWORKS_NODE
#define BAYESIANNETWORKS_NODE

#include <sstream>
#include <sha1.h>
#include "Node.h"

std::string Node::get_name() const {
    return name;
}

std::unordered_map<std::string, int> Node::get_states_map() const {
    return states_map;
}

std::vector<std::string> Node::get_states() const {
    return states;
}



std::vector<std::string> Node::get_parents() const {
    return parents;
}

std::string Node::hash_fun(const std::string& h) {

    Chocobo1::SHA1 hash;
    hash.addData(h.c_str(), h.size()).finalize();
    return hash.toString();
}

void Node::set_probabilities(const std::shared_ptr<std::vector<std::vector<float>>> &probabilities, const std::string& hashedCpt) {
    this->probabilities = probabilities;
    this->hashedCPT = hashedCpt; // the new hash
    //    std::cout<<"Number of pointers: "<<probabilities.use_count()<<std::endl;
}

void Node::probs_check_delete(const std::string& hashedCPT) {
    if (Node::probs_hashmap[hashedCPT].use_count() == 1) {
        Node::probs_hashmap[hashedCPT].reset();
        Node::probs_hashmap.erase(hashedCPT);
    }
}

std::string Node::get_hashed_cpt() const {
    return hashedCPT;
}

std::vector<unsigned int> Node::get_parent_weight_states() const {
    return parent_wstates;
}


#endif //BAYESIANNETWORKS_NODE


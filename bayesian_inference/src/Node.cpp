#ifndef BAYESIANNETWORKS_NODE
#define BAYESIANNETWORKS_NODE

#include <sstream>
#include <sha1.h>
#include "Node.h"

std::string Node::getName() const {
    return name;
}

std::unordered_map<std::string, int> Node::getStatesMap() const {
    return states_map;
}

std::vector<std::string> Node::getStates() const {
    return states;
}



std::vector<std::string> Node::getParents() const {
    return parents;
}

std::string Node::hashFun(const std::string& raw) {

    Chocobo1::SHA1 hash;
    hash.addData(raw.c_str(), raw.size()).finalize();
    return hash.toString();
}

void Node::setProbabilities(const std::shared_ptr<std::vector<std::vector<float>>> &probabilities, const std::string& hashedCpt) {
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

std::string Node::getHashedCPT() const {
    return hashedCPT;
}

std::vector<unsigned int> Node::getParentWeightStates() const {
    return parent_wstates;
}


#endif //BAYESIANNETWORKS_NODE


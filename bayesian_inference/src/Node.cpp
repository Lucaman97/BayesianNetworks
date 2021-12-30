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

std::vector<std::vector<float>> Node::getProbabilities() const {
    return *probabilities;
}

std::vector<std::string> Node::getParents() const {
    return parents;
}




std::string Node::hashFun(const std::string& raw) {

    Chocobo1::SHA1 hash;
    hash.addData(raw.c_str(), raw.size()).finalize();
    return hash.toString();
}

void Node::setProbabilities(const std::shared_ptr<std::vector<std::vector<float>>> &probabilities) {
    this->probabilities = probabilities;
    //    std::cout<<"Number of pointers: "<<probabilities.use_count()<<std::endl;
}

void Node::probs_check_delete(){
    std::string hash;
    for(auto &e : Node::probs_hashmap){
        hash = e.first;

        if (Node::probs_hashmap[hash].use_count() == 1) {
            std::cout<<"Deleting node"<<std::endl;
            //Node::probs_hashmap.erase(hash);
            break;
        }
    }

    Node::probs_hashmap.erase(hash);
}

#endif //BAYESIANNETWORKS_NODE


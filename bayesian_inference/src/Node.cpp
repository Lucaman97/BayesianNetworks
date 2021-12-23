#ifndef BAYESIANNETWORKS_NODE
#define BAYESIANNETWORKS_NODE

#include <sstream>
#include <utility>
#include <sha1.h>
#include "Node.h"
//#include "../extern/hashLibrary/sha1.h"

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


/*
Node::Node(std::string name, std::vector<std::string> states, std::unordered_map<std::string, int> states_map,
           std::shared_ptr<std::vector<std::vector<float>>> probabilities, std::vector<std::string> parents, int n_states)
{
    this->name = (std::move(name));
    this->states = std::move(states);
    this->states_map = (std::move(states_map));
    this->parents = (std::move(parents));
    this->n_states = (std::move(n_states));
    this->probabilities = std::move(probabilities);
}*/

void Node::setHashmapList(const std::string& newList) {

    //if hash(probabilities) is not in probs_hashmap, then add it,
    // else make the probabilities pointer point the one already existing

    std::string hashedCPT = hashFun(newList);
    std::istringstream ss(newList);
    std::string prob;
    int states_counter = 0;
    //If the hashmap does not contain the node, then:
    if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end())
    {
        std::vector<float> firstLayerVec;
        std::vector<std::vector<float>> secondLayerVec;
        //Node::probs_hashmap[hash.toString()].push_back(firstLayerVec);
        while (ss >> prob)
        {
            //let's add the probabilities to the hashmap: the hashed probabilities are the key.
            // 'i' is the vector index

            firstLayerVec.push_back(std::stof(prob));
            //Node::probs_hashmap[hash.toString()][i].push_back(std::stof(prob));

            //probabilities[i].push_back(std::stof(prob));
            states_counter++;
            if (states_counter == this->n_states)
            {
                secondLayerVec.emplace_back(firstLayerVec);
                //std::vector<float> firstLayerVec;
                firstLayerVec.clear();
                states_counter = 0;
                //  i++;
                //Node::probs_hashmap[hash.toString()].emplace_back(firstLayerVec);
            }
        }
        Node::probs_hashmap[hashedCPT] = std::make_shared<std::vector<std::vector<float>>>(secondLayerVec);
    }
}

std::string Node::hashFun(const std::string& raw) {

    Chocobo1::SHA1 hash;
    hash.addData(raw.c_str(), raw.size()).finalize();
    return hash.toString();
}

void Node::setProbabilities(const std::shared_ptr<std::vector<std::vector<float>>> &probabilities) {
    this->probabilities = probabilities;
}


#endif //BAYESIANNETWORKS_NODE


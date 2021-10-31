#include "Node.h"

std::string Node::getName() const {
    return name;
}

std::vector<std::string> Node::getStates() const {
    return states;
}

std::vector<float> Node::getProbabilities() const {
    return probabilities;
}

std::vector<std::string> Node::getParents() const {
    return parents;
}



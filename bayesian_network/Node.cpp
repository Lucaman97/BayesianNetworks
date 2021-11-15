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

Node::Node(std::string name, std::vector<std::string> states, std::unordered_map<std::string, int> states_map,
           std::vector<std::vector<float>> probabilities, std::vector<std::string> parents) :
        name(std::move(name)), states(std::move(states)), states_map(std::move(states_map)),
        parents(std::move(parents))
{
    this->probabilities = std::make_shared<std::vector<std::vector<float>>>(probabilities);

}



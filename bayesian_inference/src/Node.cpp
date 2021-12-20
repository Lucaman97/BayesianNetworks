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
    return *ptr();
}

std::vector<std::string> Node::getParents() const {
    return parents;
}

Node::Node(std::string name, std::vector<std::string> states, std::unordered_map<std::string, int> states_map,
           const std::vector<std::vector<float>>& probabilities, std::vector<std::string> parents)
{
    construct();
    this->name = (std::move(name));
    this->states = (std::move(states));
    this->states_map = (std::move(states_map));
    this->parents = (std::move(parents));
    *ptr() = (probabilities);

    /*
    if (this->name == "Profession") {
        for (auto& v : this->getProbabilities()) {
            for (auto& p : v) {
                std::cout << p << " ";
            }
            std::cout << "\n";
        }
    }
    */
}


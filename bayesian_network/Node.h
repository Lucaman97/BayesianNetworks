#ifndef PROGETTO_NODE_H
#define PROGETTO_NODE_H

#include <iostream>
#include <utility>
#include <vector>

// this class will contain a CPT
class Node {
public:
    explicit Node(std::string name, std::vector<std::string> states, std::vector<float> probabilities, std::vector<std::string> parents) :
        name(std::move(name)), states(std::move(states)), probabilities(std::move(probabilities)), parents(std::move(parents)) {};
    std::string getName() const;
    std::vector<std::string> getStates() const;
    std::vector<float> getProbabilities() const;
    std::vector<std::string> getParents() const;
private:
    std::string name;
    std::vector<std::string> states;
    std::vector<float> probabilities;
    //std::vector<std::shared_ptr<Node>> parents; // oppure weak_ptr, ancora non so se un riferimento al padre potrà tornare utile
    std::vector<std::string> parents;
};


#endif //PROGETTO_NODE_H

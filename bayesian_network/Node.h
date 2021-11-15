#ifndef PROGETTO_NODE_H
#define PROGETTO_NODE_H

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <memory>

// this class will contain a CPT
class Node {
public:
    explicit Node(std::string name, std::vector<std::string> states, std::unordered_map<std::string, int> states_map,
                  std::vector<std::vector<float>> probabilities, std::vector<std::string> parents);
    //: name(std::move(name)), states(std::move(states)), states_map(std::move(states_map)),
    // probabilities(std::move(probabilities)), parents(std::move(parents)) {};
    std::string getName() const;
    std::unordered_map<std::string, int> getStatesMap() const;
    std::vector<std::string> getStates() const;
    std::vector<std::vector<float>> getProbabilities() const;
    std::vector<std::string> getParents() const;

private:
    std::string name;
    // I assume that the number of states of a node is not very large (I could use a map or only a vector, but it would be slower)
    std::unordered_map<std::string,int> states_map; // state,index
    std::vector<std::string> states;
    std::vector<std::string> parents;


    std::shared_ptr<std::vector<std::vector<float>>> probabilities;

    static std::unordered_map<std::string, std::vector<std::vector<float>>> probs_hashmap;

    //static std::unordered_map<std::string, std::string> probs_hashmap;
};


#endif //PROGETTO_NODE_H

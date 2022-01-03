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
    explicit inline Node(std::string name, std::vector<std::string> states, std::unordered_map<std::string, int> states_map,
                  std::shared_ptr<std::vector<std::vector<float>>> probabilities, std::vector<std::string> parents, int n_states, std::string hashedCPT)
            : name(std::move(name)), states(std::move(states)), states_map(std::move(states_map)),
            parents(std::move(parents)), hashedCPT(std::move(hashedCPT))
            {this->probabilities=(std::move(probabilities));};


    std::string getName() const;
    static std::string hashFun(const std::string&);
    std::unordered_map<std::string, int> getStatesMap() const;
    std::vector<std::string> getStates() const;
    std::vector<std::vector<float>> getProbabilities() const;
    void setProbabilities(const std::shared_ptr<std::vector<std::vector<float>>>& probabilities, const std::string& hashedCpt);
    std::vector<std::string> getParents() const;
    std::string getHashedCPT() const;
    static std::unordered_map<std::string, std::shared_ptr<std::vector<std::vector<float>>>> probs_hashmap;
    static void probs_check_delete(const std::string& hashedCPT);


private:
    std::string name;
    // I assume that the number of states of a node is not very large (I could use a map or only a vector, but it would be slower)
    std::unordered_map<std::string,int> states_map; // state,index
    std::vector<std::string> states;
    std::vector<std::string> parents;
    std::string hashedCPT;
    int n_states;

};


#endif //PROGETTO_NODE_H

#ifndef PROGETTO_NODE_H
#define PROGETTO_NODE_H
#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <memory>
#include "COWBase.h"
class Node : COWBase<std::vector<std::vector<float>>>{
public:
    explicit Node(std::string name, std::vector<std::string> states, std::unordered_map<std::string, int> states_map,
                  std::shared_ptr<std::vector<std::vector<float>>> probabilities, std::vector<std::string> parents, int n_states)
            : name(std::move(name)), states(std::move(states)), states_map(std::move(states_map)),
             probabilities(std::move(probabilities)), parents(std::move(parents)) {};

    std::string getName() const;
    void setHashmapList(const std::string& newList);
    static std::string hashFun(const std::string&);
    std::unordered_map<std::string, int> getStatesMap() const;
    std::vector<std::string> getStates() const;
    std::vector<std::vector<float>> getProbabilities() const;
    void setProbabilities(const std::shared_ptr<std::vector<std::vector<float>>>& probabilities);
    std::vector<std::string> getParents() const;

    static std::unordered_map<std::string, std::shared_ptr<std::vector<std::vector<float>>>> probs_hashmap;

    long use_count() const
    {
        return probabilities.use_count();
    }

private:
    std::string name;
    // I assume that the number of states of a node is not very large (I could use a map or only a vector, but it would be slower)
    std::unordered_map<std::string,int> states_map; // state,index
    std::vector<std::string> states;
    std::vector<std::string> parents;
    std::shared_ptr<std::vector<std::vector<float>>> probabilities;
    int n_states;
    //std::shared_ptr<std::vector<std::vector<float>>> probabilities;
    // + m_ptr that is the pointer to the actual probabilities matrix
    
    //static std::unordered_map<std::string, std::string> probs_hashmap;
};


#endif //PROGETTO_NODE_H

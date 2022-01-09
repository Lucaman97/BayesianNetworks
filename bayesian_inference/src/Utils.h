#ifndef BAYESIANNETWORKS_UTILS_H
#define BAYESIANNETWORKS_UTILS_H

#include <iostream>
#include <vector>

#include <unordered_map>

//namespace for utilities
namespace utils {
    //given a string as input it counts the number of words (space separated strings)
    int word_count(const std::string& input);

    //given an input and a char it split the string using the char as delimiter
    std::vector<std::string> split_string(const std::string& input, char delim);

    //returns the size of a cpt
    int calc_cpt_size(const std::vector<std::vector<float>>& cpt);




    std::vector<float> normalize(const std::vector<float>& posteriors);

};


#endif //BAYESIANNETWORKS_UTILS_H

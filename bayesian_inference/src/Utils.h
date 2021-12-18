#ifndef BAYESIANNETWORKS_UTILS_H
#define BAYESIANNETWORKS_UTILS_H

#include <iostream>
#include <vector>

class Utils {
public:
    static int word_count(const std::string& input);
    static std::vector<std::string> split_string(const std::string& input, char delim);
};


#endif //BAYESIANNETWORKS_UTILS_H

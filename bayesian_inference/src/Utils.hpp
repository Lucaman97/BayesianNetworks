#ifndef BAYESIANNETWORKS_UTILS_HPP
#define BAYESIANNETWORKS_UTILS_HPP

#include <cctype>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

//namespace for utilities
namespace utils {
    //returns the size of a cpt
    template <typename T>
    size_t calc_cpt_size(const std::vector<std::vector<T>>& cpt);

    // normalizes the occurrencies of the input states and returns the conditional probabilites
    template <typename T>
    std::vector<T> normalize(const std::vector<T>& posteriors);

    //given a string as input it counts the number of words (space separated strings)
    int word_count(const std::string &input);

    //given an input and a char it split the string using the char as delimiter
    std::vector<std::string> split_string(const std::string &input, char delim);
}

template <typename T>
size_t utils::calc_cpt_size(const std::vector<std::vector<T>>& cpt) {
    size_t size = 0;
    for (auto& row : cpt) {
        size += row.size();
    }
    return size;
}

template <typename T>
std::vector<T> utils::normalize(const std::vector<T>& posteriors) {
    std::vector<T> normalized_post(posteriors.size());
    float sum = 0;
    for (T posterior: posteriors)
        sum += posterior;
    for (int i = 0; i < posteriors.size(); i++) {
        T posterior = posteriors[i];
        posterior /= sum;
        posterior = round(posterior * 100.0) / 100.0;
        normalized_post[i] = posterior;
    }
    return normalized_post;
}

#endif //BAYESIANNETWORKS_UTILS_HPP

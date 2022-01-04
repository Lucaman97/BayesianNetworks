#include "Utils.h"
#include <cctype>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>

int Utils::word_count(const std::string &input) {
    int count = 1;
    for (char c : input) {
        if (c == ' ')
            count++;
    }
    return count;
}

std::vector<std::string> Utils::split_string(const std::string &input, char delim) {
        std::vector<std::string> tokens;
        std::stringstream check(input);
        std::string intermediate;

        while (getline(check, intermediate, delim)) {
            intermediate.erase(std::remove_if(intermediate.begin(), intermediate.end(), ::isspace), intermediate.end()); // removes leading and trailing whitespaces
            tokens.push_back(intermediate);
        }

        return tokens;
}

int Utils::calc_cpt_size(const std::vector<std::vector<float>>& cpt) {
    int size = 0;
    for (auto& row : cpt) {
        size += row.size();
    }
    return size;
}

std::vector<float> Utils::normalize(const std::vector<float>& posteriors) {
    std::vector<float> normalized_post(posteriors.size());
    float sum = 0;
    for (float posterior: posteriors)
        sum += posterior;
    for (int i = 0; i < posteriors.size(); i++) {
        float posterior = posteriors[i];
        posterior /= sum;
        posterior = round(posterior * 100.0) / 100.0;
        normalized_post[i] = posterior;
    }
    return normalized_post;
}

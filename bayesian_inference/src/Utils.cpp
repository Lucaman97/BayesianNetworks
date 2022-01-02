#include "Utils.h"
#include <sstream>

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

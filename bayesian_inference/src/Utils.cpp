#include "Utils.hpp"

int utils::word_count(const std::string &input) {
    int count = 1;
    for (char c : input) {
        if (c == ' ')
            count++;
    }
    return count;
}

std::vector<std::string> utils::split_string(const std::string &input, char delim) {
    std::vector<std::string> tokens;
    std::stringstream check(input);
    std::string intermediate;

    while (getline(check, intermediate, delim)) {
        intermediate.erase(std::remove_if(intermediate.begin(), intermediate.end(), ::isspace), intermediate.end()); // removes leading and trailing whitespaces
        tokens.push_back(intermediate);
    }

    return tokens;
}


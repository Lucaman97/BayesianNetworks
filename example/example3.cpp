#include <iostream>
#include "bayinf/Graph.h"
#include <string>
#include <chrono>
#include <vector>


int main(){
    std::cout<<"START Example3"<<std::endl<<"------------------------\n";
    std::cout<<"Test with 'deterministic' tags"<<std::endl;
    bayinf::Graph network("data/Animals.xdsl");
    int num_samples = 10000;

    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, std::vector<float>> results = network.inference(num_samples);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    float seconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()/(float)1000000;
    std::cout << "Took " << seconds << " s\n"<<std::endl;
    bayinf::Graph::pretty_print(results);

    return 0;
}


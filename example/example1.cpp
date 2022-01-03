#include <iostream>
#include "bayinf/Graph.h"
#include <string>
#include <chrono>
#include <vector>

/*
 * HOW TO USE
 *
 * To perform inference use -> network.inference(num_samples,evidence,algorithm)
 *
 * num_samples is 1000 by default
 * evidence is empty by default, in this way I can perform inference without evidence
 * algorithm can be:
 *      0: likelihood weighting (deafult)
 *      1: rejection sampling
 *
 */

int main() {
    std::cout<<"START"<<std::endl<<"------------------------\n";

    bayinf::Graph network("data/Credit.xdsl");
    int num_samples = 10000;

    // vanilla network (no evidence)
    std::unordered_map<std::string, std::vector<float>> results = network.inference(num_samples);
    bayinf::Graph::pretty_print(results);

    // set evidence
    std::string evidence = "CreditWorthiness=Negative,Assets=wealthy";
    results = network.inference(num_samples, evidence);
    bayinf::Graph::pretty_print(results); // print results in a nice format

    // now with bad formatted evidences
    evidence = "CreditWooorthiness=Negative,Assets=wealthy";
    std::cout << "Should throw an exception:\n";
    results = network.inference(num_samples, evidence);
    bayinf::Graph::pretty_print(results);

    return 0;
}

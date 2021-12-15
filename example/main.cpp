#include <iostream>
#include "bayinf/Graph.h"
#include <string>
#include <chrono>
#include <vector>

int main() {
    bayinf::Graph network("data/Credit.xdsl");

    auto start = std::chrono::high_resolution_clock::now();
    int num_samples = 10000;
    // how to write a query (scrivi solo la roba dentro le parentesi) -> P(MetastCancer|Coma=present,IncrSerCal=absent)
    std::string query = "Profession|CreditWorthiness=Negative";
    //std::string query = "ins_sens|glu_prod_16=x2_0mmol_kg_h";
    std::vector<float> posteriors = network.likelihood_weighting(query, num_samples); // try to change 'likelihood_weighting' with 'rejection_sampling'

    std::cout << "P(" << query << ") = <";
    for (int i = 0; i < posteriors.size()-1; i++)
        std::cout << posteriors[i] << ",";
    std::cout << posteriors[posteriors.size()-1] << ">\n";

    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    float seconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()/(float)1000000;

    std::cout << "Took " << seconds << " s\n";

/*
// If you are using C++14 or C++17, don't forget the "gsl" folder!

        // Get an instance
        Chocobo1::SHA1 sha1;

        // Feed data & data length to it
        sha1.addData("hello");


        sha1.finalize();

        std::string result = sha1.toString();
        std::cout<<std::endl<<result; */

    return 0;
}



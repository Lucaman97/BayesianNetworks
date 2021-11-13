#include <iostream>
#include "Graph.h"
#include "CPTable.h"
#include <string>

int main() {
    /*
    Graph network;
    network.create_node("Burglar");
    network.create_node("Racoon");
    network.create_node("Dog");

    network.create_edge("Burglar", "Dog");
    network.create_edge("Racoon", "Dog");
    */

    //CPTable gigio("Coma.xdsl");

    Graph network("Credit.xdsl");
    //std::cout << network;

    /*
    int num_samples = 10000;
    float p = 0;
    for (int i = 0; i < num_samples; i++) {
        std::unordered_map<std::string,std::string> sample = network.prior_sample();
        if (sample["Worth"] == "Low")
            p++;
    }
    p /= (float)num_samples;
    std::cout << p << "\n";
    */

    int num_samples = 1000; // try low number of samples to see the benefits of likelihood_weighting over rejection_sampling
    // how to write a query (scrivi solo la roba dentro le parentesi) -> P(MetastCancer|Coma=present,IncrSerCal=absent)
    std::string query = "Profession|CreditWorthiness=Negative";
    std::vector<float> posteriors = network.likelihood_weighting(query, num_samples); // try to change 'likelihood_weighting' with 'rejection_sampling'

    for (float & posterior : posteriors)
        posterior = round(posterior * 100.0)/100.0; // arrotonda a due cifre dopo la virgola

    std::cout << "P(" << query << ") = <";
    for (int i = 0; i < posteriors.size()-1; i++)
        std::cout << posteriors[i] << ",";
    std::cout << posteriors[posteriors.size()-1] << ">\n";
    return 0;
}



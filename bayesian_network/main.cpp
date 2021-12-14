#include <iostream>
#include "Graph.h"
#include "CPTable.h"
#include <string>
#include <chrono>
//#include "hashLibrary/sha1.h"


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
    auto start = std::chrono::high_resolution_clock::now();
    int num_samples = 10000;
    // how to write a query (scrivi solo la roba dentro le parentesi) -> P(MetastCancer|Coma=present,IncrSerCal=absent)
    std::string query = "Profession|CreditWorthiness=Negative";
    //std::string query = "ins_sens|glu_prod_16=x2_0mmol_kg_h";
    std::vector<float> posteriors = network.likelihood_weighting(query, num_samples); // try to change 'likelihood_weighting' with 'rejection_sampling'

    for (float & posterior : posteriors)
        posterior = round(posterior * 100.0)/100.0; // arrotonda a due cifre dopo la virgola

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



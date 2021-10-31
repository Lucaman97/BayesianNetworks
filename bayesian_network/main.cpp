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

    Graph network("Coma.xdsl");
    std::cout << network << '\n';

    // just debugging
    std::vector<float> probs =  network.getNode("BrainTumor")->getProbabilities();
    std::cout << "Probabilities of BrainTumor: ";
    for (float p : probs) {
        std::cout << p << " ";
    }
    std::cout << "\n";

    std::vector<std::string> parents = network.getNode("Coma")->getParents();
    std::cout << "Parents of Coma: ";
    for (const std::string& p : parents) {
        std::cout << p << " ";
    }
    std::cout << "\n";
    return 0;
}



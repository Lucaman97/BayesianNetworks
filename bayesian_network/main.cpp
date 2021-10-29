#include <iostream>
#include "Graph.h"
#include "CPTable.h"
int main() {
    Graph network;
    network.create_node("Burglar");
    network.create_node("Racoon");
    network.create_node("Dog");

    network.create_edge("Burglar", "Dog");
    network.create_edge("Racoon", "Dog");

    std::cout << network << '\n';

    CPTable gigio("Coma.xdsl");
    return 0;
}



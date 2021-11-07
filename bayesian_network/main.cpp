#include <iostream>
#include "Graph.h"
#include "CPTable.h"

int main() {

    Graph network("Coma.xdsl");

    std::cout << network << '\n';

    //CPTable gigio("Coma.xdsl");
    return 0;
}



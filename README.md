# BayesianNetworks
This library is designed to easily perform inference on belief networks 

## Getting started
* Include bayesian_inference in your source files
* Add this line to your executable `#include "baynet/Graph.h"`
* Add the library in the `CMakeLists.txt` like this
```
target_link_libraries(${PROJECT_NAME} baynet)
```

## Usage
### Loading the network
Put the xdsl file containing the network in the data folder, then load the network by passing the file name to the constructor
```
// load the network contained in Credit.xdsl
baynet::Graph network("data/Credit.xdsl");
```

### See the initial state of the network
To see the prior probabilities of each node, just call the inference method like this
```
std::unordered_map<std::string, std::vector<float>> results = network.inference(num_samples);

// use this to print the network in a nice format
baynet::Graph::pretty_print(results);
```

### Set the evidence
Write the evidence variables, separating them with a comma, then pass the string to the inference method. You can also decide to pass `1` if you want to use rejection sampling (default is likelihood weighting)
```
std::string evidence = "CreditWorthiness=Negative,Assets=wealthy"; // if there is a space after the comma it doesn't matter
results = network.inference(num_samples, evidence); // network.inference(num_samples, evidence, 1) to use rejection sampling
baynet::Graph::pretty_print(results); // see the results
```
If you are interested only in a single node, you can save a lot of computational time by calling single_node_inference.
```
// Let's calculate P(VisitToAsia|Tuberculosis=Present)
std::string query = "VisitToAsia|Tuberculosis=Present"; // set the query
std::vector<float> results = network.single_node_inference(query, num_samples); // obtain the conditional probabilities
baynet::Graph::pretty_print_query(results, query); // print the result
```

### Edit the network
If you want, you can change the CPT of a node, given its name
```
// make sure the number of probabilities matches the CPT of the node you want to edit
std::string problist = "0.5 0.42 0.08";
network.edit_cpt("Income", problist);
```

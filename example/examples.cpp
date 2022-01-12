#include <iostream>
#include "baynet/Graph.h"
#include <string>
#include <chrono>
#include <vector>
#include "../src/Utils.hpp"


void example1() {
    std::cout<<"START Example1"<<std::endl<<"------------------------\n";

    baynet::Graph network("data/Credit.xdsl");
    int num_samples = 10000;

    // vanilla network (no evidence)
    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, std::vector<float>> results = network.inference(num_samples);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    float seconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()/(float)1000000;
    std::cout << "Took " << seconds << " s\n"<<std::endl;
    baynet::Graph::pretty_print(results);

    // set evidence
    std::string evidence = "CreditWorthiness=Negative,Assets=wealthy";
    results = network.inference(num_samples, evidence);
    baynet::Graph::pretty_print(results); // print results in a nice format

    // now with bad formatted evidences
    evidence = "CreditWooorthiness=Negative,Assets=wealthy";
    std::cout << "Should throw an exception:\n";
    results = network.inference(num_samples, evidence);
    baynet::Graph::pretty_print(results);

}

void example2() {
    std::cout<<"START Example2"<<std::endl<<"------------------------"<<std::endl;
    std::cout<<"Graph modification test"<<std::endl;
    baynet::Graph network("data/Credit.xdsl");


    std::cout<<"\n\n------------------------"<<std::endl;
    std::cout<< "BEFORE MODIFICATION:"<<std::endl;
    //std::cout<<"Map dimension: "<<network.get_map_size()<<std::endl;
    network.print_node("Income");
    auto backup1 = network.node_list[network.node_indexes["Income"]].get_hashed_cpt();

    system("pause");
    std::cout<<"\n\nNow let's try to edit a cpt."<<std::endl;


    network.edit_cpt("Income", "0.5 0.42 0.08");
    std::cout << "Modified Income: 0.5, 0.42, 0.08"<<std::endl;
    std::cout <<"\nOld cpt count: "<<Node::probs_hashmap[backup1].use_count();
    backup1 = network.node_list[network.node_indexes["Income"]].get_hashed_cpt();


    std::cout<< "\nAFTER MODIFICATION:"<<std::endl;



    //std::cout<<"Map dimension: "<<network.get_map_size()<<std::endl;
    network.print_node("Income");

    system("pause");
    std::cout<<"\n\nnow let's try to edit a cpt again:"<<std::endl;
    network.edit_cpt("Income", "0.333333 0.333333 0.333333");
    std::cout << "Modified Income: 0.333333, 0.333333, 0.333333"<<std::endl;
    std::cout <<"\nOld cpt count: "<<Node::probs_hashmap[backup1].use_count();

    std::cout<< "\nAFTER SECOND MODIFICATION:"<<std::endl;

    network.print_node("Income");


}

void example3(){
    std::cout<<"START Example3"<<std::endl<<"------------------------\n";
    std::cout<<"Test with 'deterministic' tags"<<std::endl;
    baynet::Graph network("data/Animals.xdsl");
    int num_samples = 10000;

    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, std::vector<float>> results = network.inference(num_samples);
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    float seconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()/(float)1000000;
    std::cout << "Took " << seconds << " s\n"<<std::endl;
    baynet::Graph::pretty_print(results);

    // set evidence
    std::string evidence = "Class=Bird";
    results = network.inference(num_samples, evidence);
    baynet::Graph::pretty_print(results); // print results in a nice format
}


void example4() {
    std::cout<<"START Example4"<<std::endl<<"------------------------\n";

    baynet::Graph network("data/AsiaDiagnosis.xdsl");
    int num_samples = 10000;

    // set query
    std::string query = "VisitToAsia|Tuberculosis=Present";
    std::vector<float> results = network.single_node_inference(query, num_samples);
    baynet::Graph::pretty_print_query(results, query);

    std::cout<<"\n\nPrint a Node: "<<std::endl;
    network.print_node("VisitToAsia");

    std::cout<<"\n\nPrint the hashmap: "<<std::endl;
    network.print_map();

}

/*
 * Perform inference on a single node
 */
void example5() {
    std::cout<<"START Example5"<<std::endl<<"------------------------\n";

    baynet::Graph network("data/Credit.xdsl");
    int num_samples = 10000;

    std::string query = "Worth|CreditWorthiness=Negative,Assets=wealthy";

    std::vector<float> results = network.single_node_inference(query, num_samples);
    baynet::Graph::pretty_print_query(results, query);

}
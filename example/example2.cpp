#include <iostream>
#include "bayinf/Graph.h"
#include <string>
#include <chrono>
#include <vector>
#include "../src/Utils.h"


//Function to print the probabilities of a single node given the evidence: query = something|evidence
void printSingleQuery(std::unordered_map<std::string, std::vector<float>> results, std::string query){
    std::cout << "P(" << query<< ") = <";
    int count=0;
    for (auto it = results[query].begin(); it != results[query].end(); it++){
        if(count != results[query].size()-1)
            std::cout << *it << ",";
        else std::cout <<*it;
        count++;
    }
    std::cout << ">"<<std::endl;
}



int main() {
    std::cout<<"START Example2"<<std::endl<<"------------------------"<<std::endl;
    std::cout<<"Graph modification test"<<std::endl;
    bayinf::Graph network("data/Credit.xdsl");

    auto start = std::chrono::high_resolution_clock::now();
    int num_samples = 10000;

    // how to write a query :write only the string between brackets
    std::string query = "Worth|CreditWorthiness=Negative"; // Credit
    //std::string query = "ins_sens|glu_prod_16=x2_0mmol_kg_h"; // Diabetes
    //std::string query = "Animal|Environment=Land"; // Animals
    //std::string query ="adasdasd|CreditWorthiness=True"; // wrong query to test exception.

    //auto results = network.inference(num_samples,Utils::split_string(query,'|')[1]); // try to change 'likelihood_weighting' with 'rejection_sampling'
    //bayinf::Graph::pretty_print(results);
    //printSingleQuery(results, query);



    auto elapsed = std::chrono::high_resolution_clock::now() - start;

    float seconds = (float)std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()/(float)1000000;

    std::cout << "Took " << seconds << " s"<<std::endl;
    //---------------------------------------------------

    std::cout<<"\n\n------------------------"<<std::endl;
    std::cout<< "BEFORE MODIFICATION:"<<std::endl;
    //std::cout<<"Map dimension: "<<network.getMapSize()<<std::endl;
    network.printNode("Income");
    auto backup1 = network.node_list[network.node_indexes["Income"]].getHashedCPT();
    //network.printMap();
    system("pause");
    std::cout<<"\n\nNow let's try to edit a cpt."<<std::endl;


    network.edit_cpt("Income", "0.5 0.42 0.08");
    std::cout << "Modified Income: 0.5, 0.42, 0.08"<<std::endl;
    std::cout <<"\nOld cpt count: "<<Node::probs_hashmap[backup1].use_count();
    backup1 = network.node_list[network.node_indexes["Income"]].getHashedCPT();

    //results = network.inference(num_samples,Utils::split_string(query,'|')[1]); // try to change 'likelihood_weighting' with 'rejection_sampling'
    //printSingleQuery(results, query);

    std::cout<< "\nAFTER MODIFICATION:"<<std::endl;



    //std::cout<<"Map dimension: "<<network.getMapSize()<<std::endl<<std::endl;
    network.printNode("Income");
    //network.printMap();
    system("pause");
    std::cout<<"\n\nnow let's try to edit a cpt again:"<<std::endl;
    network.edit_cpt("Income", "0.333333 0.333333 0.333333");
    std::cout << "Modified Income: 0.333333, 0.333333, 0.333333"<<std::endl;
    std::cout <<"\nOld cpt count: "<<Node::probs_hashmap[backup1].use_count();

    std::cout<< "\nAFTER SECOND MODIFICATION:"<<std::endl;

    network.printNode("Income");

    /*
    std::cout << "P(" << query << ") = <";
    for (int i = 0; i < posteriors.size()-1; i++)
        std::cout << posteriors[i] << ",";
    std::cout << posteriors[posteriors.size()-1] << ">"<<std::endl;

    std::cout<< "After modifying:"<<std::endl;
    for(auto &node : network.node_list){
        if(node.getName() == "Debit"){
            std::cout<<"Counter: "<<node.use_count()<<std::endl;
        }
    }

    std::cout<<"Map dimension: "<<network.getMapSize()<<std::endl;
    network.printNode("Income");
    network.printMap();
    std::cout<<"------------------------"<<std::endl;

    std::cout<<"Let's edit again the cpt:"<<std::endl;
    network.edit_cpt("Income", "0.5 0.42 0.08");
    std::cout << "Modified Income: 0.5, 0.42, 0.08"<<std::endl;

    posteriors = network.likelihood_weighting(query, num_samples);

    std::cout << "P(" << query << ") = <";
    for (int i = 0; i < posteriors.size()-1; i++)
        std::cout << posteriors[i] << ",";
    std::cout << posteriors[posteriors.size()-1] << ">"<<std::endl;

    std::cout<<std::endl;
    std::cout<< "After modifying for the second time:"<<std::endl;
    for(auto &node : network.node_list){
        if(node.getName() == "Debit"){
            std::cout<<"Counter: "<<node.use_count()<<std::endl;
        }
    }
    std::cout<<"Map dimension: "<<network.getMapSize()<<std::endl;
    network.printNode("Income");
    network.printMap();
    std::cout<<"------------------------"<<std::endl;
    return 0;
     */
}



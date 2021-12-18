#include "bayinf/Graph.h"
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <future>
#include "../extern/tinyxml2/tinyxml2.h"
#include "../extern/hashLibrary/sha1.h"
#include "Utils.h"


//Define the static member
std::unordered_map<std::string, std::vector<std::vector<float>>> Node::probs_hashmap;

bayinf::Graph::Graph(const std::string &filename)
{

    tinyxml2::XMLDocument doc;
    try {
        tinyxml2::XMLError err_id = doc.LoadFile(("../../" + filename).c_str());
        if (err_id != 0) {
            throw err_id;
        }

        tinyxml2::XMLElement* root = doc.FirstChildElement("smile")->FirstChildElement("nodes" );

        //std::unordered_map<std::string, int> parent_nstates; // useful to load the cpt, because the number of columns of every cpt is equal to the product of the number of states of the parents

        // iterate over all the 'cpt' xml tags
        for (tinyxml2::XMLElement* e = root->FirstChildElement("cpt" ); e != nullptr; e = e->NextSiblingElement("cpt")) {
            const char* node_id;
            e->QueryStringAttribute("id", &node_id);

            // save the states
            std::unordered_map<std::string, int> states_map;
            std::vector<std::string> states;
            int state_counter = 0;

            for (tinyxml2::XMLElement* state = e->FirstChildElement("state" ); state != nullptr; state = state->NextSiblingElement("state"))
            {
                const char* state_id;
                state->QueryStringAttribute("id", &state_id);
                states_map[state_id] = state_counter;
                states.emplace_back(state_id);
                state_counter++;
            }

            // save the parents
            std::vector<std::string> parents;
            if (e->FirstChildElement("parents") != nullptr) {
                const char* parentlist = e->FirstChildElement("parents")->GetText();
                std::istringstream ss(parentlist);
                std::string parent;
                while (ss >> parent) {
                    parents.push_back(parent);
                }
            }

            // save the probabilities
            if (e->FirstChildElement("probabilities") != nullptr) {
                std::string problist = e->FirstChildElement("probabilities")->GetText();
                int n_cols = Utils::word_count(problist)/state_counter;
                std::vector<std::vector<float>> probabilities(n_cols); // initialize num of rows
                //std::cout<<problist<<std::endl;
                //Chocobo1::SHA1 hash;
                //hash.addData(problist.c_str(), 1);
                //std::cout<<hash.finalize().toString()<<std::endl;
                std::istringstream ss(problist);
                std::string prob;
                //int i = 0;
                int n_states = 0;

                //if hash(probabilities) is not in probs_hashmap, then add it,
                // else make the probabilities pointer point the one already existing

                Chocobo1::SHA1 hash;
                hash.addData(problist.c_str(), problist.size()).finalize();

                std::string hashedCPT = hash.toString();

                //If the hashmap does not contain the node, then:
                if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end())
                {
                    std::vector<float> firstLayerVec;
                    std::vector<std::vector<float>> secondLayerVec;
                    //Node::probs_hashmap[hash.toString()].push_back(firstLayerVec);
                    while (ss >> prob)
                    {
                            //let's add the probabilities to the hashmap: the hashed probabilities are the key.
                            // 'i' is the vector index

                        firstLayerVec.push_back(std::stof(prob));
                            //Node::probs_hashmap[hash.toString()][i].push_back(std::stof(prob));

                        //probabilities[i].push_back(std::stof(prob));
                        n_states++;
                        if (n_states == state_counter)
                        {
                            secondLayerVec.emplace_back(firstLayerVec);
                            //std::vector<float> firstLayerVec;
                            firstLayerVec.clear();
                            n_states = 0;
                          //  i++;
                            //Node::probs_hashmap[hash.toString()].emplace_back(firstLayerVec);
                        }
                    }
                    Node::probs_hashmap[hashedCPT] = secondLayerVec;


                }
                //let's make the pointer (probabilities) point to the existing cpt
                probabilities = Node::probs_hashmap[hashedCPT];
                cpt_list.push_back(std::make_shared<Node>(node_id, states, states_map, probabilities, parents));
                cpt_indexes[node_id] = (int)cpt_list.size() - 1;
            }
            /*
            create_node(node_id, std::make_shared<Node>(node_id, states, states_map, probabilities, parents));

            for (const std::string& parent : parents) {
                create_edge(parent, node_id);
            }
             */
        }

        // Iterate over all 'deterministic' tags (fix repeating code)
        for (tinyxml2::XMLElement* e = root->FirstChildElement("deterministic" ); e != nullptr; e = e->NextSiblingElement("deterministic")) {
            const char* node_id;
            e->QueryStringAttribute("id", &node_id);

            // save the states
            std::unordered_map<std::string, int> states_map;
            std::vector<std::string> states;
            int state_counter = 0;

            for (tinyxml2::XMLElement* state = e->FirstChildElement("state" ); state != nullptr; state = state->NextSiblingElement("state"))
            {
                const char* state_id;
                state->QueryStringAttribute("id", &state_id);
                states_map[state_id] = state_counter;
                states.emplace_back(state_id);
                state_counter++;
            }

            // save the parents
            std::vector<std::string> parents;
            if (e->FirstChildElement("parents") != nullptr) {
                const char* parentlist = e->FirstChildElement("parents")->GetText();
                std::istringstream ss(parentlist);
                std::string parent;
                while (ss >> parent) {
                    parents.push_back(parent);
                }
            }

            // save the resulting states
            if (e->FirstChildElement("resultingstates") != nullptr) {
                std::string statelist = e->FirstChildElement("resultingstates")->GetText();
                int n_cols = Utils::word_count(statelist);
                std::vector<std::vector<float>> probabilities(n_cols); // initialize num of rows
                std::istringstream ss(statelist);
                std::string res_state;
                int n_states = 0;

                //if hash(probabilities) is not in probs_hashmap, then add it,
                // else make the probabilities pointer point the one already existing

                Chocobo1::SHA1 hash;
                hash.addData(statelist.c_str(), statelist.size()).finalize();

                std::string hashedCPT = hash.toString();

                //If the hashmap does not contain the node, then:
                if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end())
                {
                    std::vector<std::vector<float>> table;
                    while (ss >> res_state)
                    {
                        std::vector<float> row(n_cols, 0);
                        for (int i = 0; i < states.size(); i++) {
                            if (states[i] == res_state) {
                                row[i] = 1;
                                break;
                            }
                        }
                        table.push_back(row);
                    }
                    Node::probs_hashmap[hashedCPT] = table;
                }
                //let's make the pointer (probabilities) point to the existing cpt
                probabilities = Node::probs_hashmap[hashedCPT];
                cpt_list.push_back(std::make_shared<Node>(node_id, states, states_map, probabilities, parents));
                cpt_indexes[node_id] = (int)cpt_list.size() - 1;
            }
        }

        // debug
        /*
        for (auto& node : cpt_list) {
            std::cout << node->getName() << "\n";
            for (auto& row : node->getProbabilities()) {
                for (auto& el : row) {
                    std::cout << el << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }*/

    } catch (tinyxml2::XMLError err) { // catch error when loading the xdsl file
        std::cout << "LoadFile failed with errorID: " << err << "\n";
        exit(-1);
    }
}

/*
void Graph::create_node(const std::string& name, const std::shared_ptr<Node>& cpt) {
    adj_list[name].push_back(cpt);
}

void Graph::create_edge(const std::string &from, const std::string &to) {
    adj_list[from].push_back(adj_list[to].front());
}
*/
std::shared_ptr<Node> bayinf::Graph::getNode(const std::string& name) {
    for (const auto& node : cpt_list)
        if (node->getName() == name)
            return node;
    return nullptr;
}
/*
std::ostream &operator<<(std::ostream &out, const Graph &graph) {
    bool first;
    for (const auto & row : graph.adj_list) {
        first = true;
        if (row.second.size() > 0) { // don't print sink node
            for (const std::shared_ptr<Node>& node : row.second) {
                out << node->getName();
                if (first) {
                    out << " --> ";
                    first = false;
                } else {
                    out << " ";
                }
            }
            out << "\n";
        }
    }
    return out;
}*/

std::unordered_map<std::string,std::string> bayinf::Graph::prior_sample() {
    std::uniform_real_distribution<double> dis(0,1);
    std::unordered_map<std::string,std::string> sample;

    for (const std::shared_ptr<Node>& node : cpt_list) {
        unsigned int states_index = 0;
        if (!node->getParents().empty()) { // not a root node
            // retrieve the index to access the correct probabilities in the CPT given all the parents states (the current evidence)
            std::vector<unsigned int> parent_nstates;
            for (const std::string& parent : node->getParents()) {
                parent_nstates.push_back(cpt_list[cpt_indexes[parent]]->getStates().size());
            }
            for (int i = 0; i < node->getParents().size(); i++) {
                unsigned int prod = 1;
                for (int j = i+1; j < node->getParents().size(); j++) {
                    prod *= parent_nstates[j];
                }
                states_index += cpt_list[cpt_indexes[node->getParents()[i]]]->getStatesMap()[sample[node->getParents()[i]]] * prod;
            }
        }
        // now, based on the evidence, I want to access the right probabilities
        std::vector<float> cond_probs = node->getProbabilities()[states_index];

        float rand = dis(gen); // generate random number [0,1)
        for (int i = 0; i < cond_probs.size(); i++) { // I know that I have a probability for each state
            if (rand < cond_probs[i]) {
                sample[node->getName()] = node->getStates()[i]; // sample state from the distribution of the node
                break;
            }
            rand -= cond_probs[i];
        }
    }
    return sample;
}

std::tuple<std::unordered_map<std::string,std::string>, float> bayinf::Graph::weighted_sample(const std::unordered_map<std::string, std::string>& evidence) {
    std::uniform_real_distribution<double> dis(0,1);
    std::unordered_map<std::string,std::string> sample;
    float w = 1;
    for (const std::shared_ptr<Node>& node : cpt_list) {
        unsigned int states_index = 0;

        bool is_evidence = false;
        for (auto& e : evidence) {
            if (e.first == node->getName()) {
                is_evidence = true;
                sample[node->getName()] = e.second;
                break;
            }
        }

        if (!node->getParents().empty()) { // not a root node
            // retrieve the index to access the correct probabilities in the CPT given all the parents states (the current evidence)
            std::vector<unsigned int> parent_nstates;
            for (const std::string& parent : node->getParents()) {
                parent_nstates.push_back(cpt_list[cpt_indexes[parent]]->getStates().size());
            }
            for (int i = 0; i < node->getParents().size(); i++) {
                unsigned int prod = 1;
                for (int j = i+1; j < node->getParents().size(); j++) {
                    prod *= parent_nstates[j];
                }
                states_index += cpt_list[cpt_indexes[node->getParents()[i]]]->getStatesMap()[sample[node->getParents()[i]]] * prod;
            }
        }
        // now, based on the evidence, I want to access the right probabilities
        std::vector<float> cond_probs = node->getProbabilities()[states_index];
        if (is_evidence) {
            w *= cond_probs[node->getStatesMap()[sample[node->getName()]]];
        } else {
            float rand = dis(gen); // generate random number [0,1)
            for (int i = 0; i < cond_probs.size(); i++) { // I know that I have a probability for each state
                if (rand < cond_probs[i]) {
                    sample[node->getName()] = node->getStates()[i]; // sample state from the distribution of the node
                    break;
                }
                rand -= cond_probs[i];
            }
        }
    }
    return std::make_tuple(sample, w);
}

std::vector<float> bayinf::Graph::rejection_sampling(const std::string& query, int num_samples) {
    std::vector<std::string> tokens = Utils::split_string(query, '|');
    std::string query_variable = tokens[0];
    std::vector<std::string> evidence_variables = Utils::split_string(tokens[1], ',');
    std::unordered_map<std::string, std::string> evidence_states;
    std::vector<float> posteriors(cpt_list[cpt_indexes[query_variable]]->getStates().size(),0);

    for (const std::string& ev : evidence_variables) {
        std::vector<std::string> tok = Utils::split_string(ev, '=');
        evidence_states[tok[0]] = tok[1];
    }

    for (int i = 0; i < num_samples; i++) {
        std::unordered_map<std::string,std::string> sample = prior_sample();

        // count only the samples that are consistent with the evidence
        bool consistent = true;
        for (auto& m : evidence_states) {
            if (sample[m.first] != m.second)
                consistent = false;
        }
        if (!consistent)
            continue;

        // posteriors[index of state that has been sampled for this query variable]
        posteriors[cpt_list[cpt_indexes[query_variable]]->getStatesMap()[sample[query_variable]]]++;
    }

    // normalize
    float sum = 0;
    for (float posterior : posteriors)
        sum += posterior;
    for (float & posterior : posteriors) {
        posterior /= sum;
        posterior = round(posterior * 100.0)/100.0; // arrotonda a due cifre dopo la virgola
    }

    return posteriors;
}

std::vector<float> bayinf::Graph::likelihood_weighting(const std::string& query, int num_samples) {
    std::vector<std::string> tokens = Utils::split_string(query, '|');
    std::string query_variable = tokens[0];
    std::vector<std::string> evidence_variables = Utils::split_string(tokens[1], ',');
    std::unordered_map<std::string, std::string> evidence_states;
    std::vector<float> posteriors(cpt_list[cpt_indexes[query_variable]]->getStates().size(),0);

    for (const std::string& ev : evidence_variables) {
        std::vector<std::string> tok = Utils::split_string(ev, '=');
        evidence_states[tok[0]] = tok[1];
    }

    /*// single thread version
    for (int i = 0; i < num_samples; i++) {
        std::tuple<std::unordered_map<std::string,std::string>, float> sample_weight = weighted_sample(evidence_states);
        std::unordered_map<std::string,std::string> sample = std::get<0>(sample_weight);
        float w = std::get<1>(sample_weight);

        posteriors[cpt_list[cpt_indexes[query_variable]]->getStatesMap()[sample[query_variable]]] += w;
    }*/

    int n_thread = 3;
    //int n_thread = (int)std::thread::hardware_concurrency() - 1; // TO FIGURE OUT
    int iterations = num_samples / n_thread;
    int left = num_samples % n_thread;

    auto t_fun = [&](int iterations) {
        std::vector<float> local_posteriors(cpt_list[cpt_indexes[query_variable]]->getStates().size(),0);
        for (int i = 0; i < iterations; i++) {
            std::tuple<std::unordered_map<std::string,std::string>, float> sample_weight = weighted_sample(evidence_states);
            std::unordered_map<std::string,std::string> sample = std::get<0>(sample_weight);
            float w = std::get<1>(sample_weight);
            local_posteriors[cpt_list[cpt_indexes[query_variable]]->getStatesMap()[sample[query_variable]]] += w;
        }
        return local_posteriors;
    };

    std::vector<std::future<std::vector<float>>> t_results;
    t_results.reserve(n_thread);
    for (int i = 0; i < n_thread; i++) {
        if (i == 0)
            t_results.emplace_back(std::async(std::launch::async, t_fun, iterations + left));
        else
            t_results.emplace_back(std::async(std::launch::async, t_fun, iterations));
    }

    for (auto& res : t_results) {
        std::vector<float> loc_posteriors = res.get();
        for (int i=0; i < posteriors.size(); i++)
            posteriors[i] += loc_posteriors[i];
    }

    // normalize
    float sum = 0;
    for (float posterior : posteriors)
        sum += posterior;
    for (float & posterior : posteriors) {
        posterior /= sum;
        posterior = round(posterior * 100.0)/100.0; // arrotonda a due cifre dopo la virgola
    }

    return posteriors;
}


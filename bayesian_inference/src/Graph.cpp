#include "bayinf/Graph.h"
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <future>
#include "tinyxml2.h"
#include "Utils.h"


//Define the static member
std::unordered_map<std::string, std::shared_ptr<std::vector<std::vector<float>>>> Node::probs_hashmap;

bayinf::Graph::Graph(const std::string &filename)
{

    tinyxml2::XMLDocument doc;
    try {
        tinyxml2::XMLError err_id = doc.LoadFile(("../../" + filename).c_str());
        if (err_id != 0) {
            throw err_id;
        }

        tinyxml2::XMLElement* root = doc.FirstChildElement("smile")->FirstChildElement("nodes" );

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
                //std::vector<std::vector<float>> probabilities(n_cols); // initialize num of rows


                std::istringstream ss(problist);
                std::string prob;

                int n_states = 0;

                //if hash(probabilities) is not in probs_hashmap, then add it,
                // else make the probabilities pointer point the one already existing


                std::string hashedCPT = Node::hashFun(problist);

                //If the hashmap does not contain the node, then:
                if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end())
                {
                    std::vector<float> firstLayerVec;
                    std::vector<std::vector<float>> secondLayerVec;
                    //Node::probs_hashmap[hash.toString()].push_back(firstLayerVec);
                    while (ss >> prob)
                    {
                        firstLayerVec.push_back(std::stof(prob));
                        n_states++;
                        if (n_states == state_counter)
                        {
                            secondLayerVec.emplace_back(firstLayerVec);
                            firstLayerVec.clear();
                            n_states = 0;
                        }
                    }
                    Node::probs_hashmap[hashedCPT] = std::make_shared<std::vector<std::vector<float>>>(secondLayerVec);
                }
                Node node(node_id, states, states_map, Node::probs_hashmap[hashedCPT], parents, state_counter);
                node_list.push_back(node);
                node_indexes[node_id] = (int)node_list.size() - 1;
            }

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

                std::string hashedCPT = Node::hashFun(statelist);

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
                    Node::probs_hashmap[hashedCPT] = std::make_shared<std::vector<std::vector<float>>>(table);
                }
                //let's create the node and let's assign to it the probabilities added in probs_hashmap.
                Node node(node_id, states, states_map, Node::probs_hashmap[hashedCPT], parents, state_counter);
                node_list.push_back(node);
                node_indexes[node_id] = (int)node_list.size() - 1;

            }
        }

    } catch (tinyxml2::XMLError err) { // catch error when loading the xdsl file
        std::cout << "LoadFile failed with errorID: " << err << "\n";
        exit(-1);
    }
}

/*
void bayinf::Graph::test() {
    for (auto& node : node_list) {
        std::cout << node.getName() << "\n";
        for (auto& row : node.getProbabilities()) {
            for (auto& el : row) {
                std::cout << el << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}*/

void bayinf::Graph::edit_cpt(const std::string &name, const std::string &problist) {
    for (auto& node : node_list) {
        if (node.getName() == name) {
            int cpt_size = Utils::calc_cpt_size(node.getProbabilities());
            if (cpt_size == Utils::word_count(problist)) { // the size of the probability list must be the same as the cpt size
                int n = 0;
                int row_length = node.getStates().size();
                int n_rows = cpt_size / row_length;
                std::vector<std::vector<float>> probabilities(n_rows);
                for (auto& p : Utils::split_string(problist, ' ')) {
                    probabilities[n / row_length].push_back(std::stof(p));
                    n++;
                }
                std::string hashedCPT = Node::hashFun(problist);
                if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end()) {
                    Node::probs_hashmap[hashedCPT] = std::make_shared<std::vector<std::vector<float>>>(probabilities);
                }
                node.setProbabilities(Node::probs_hashmap[hashedCPT]);
            }
        }
    }
    void probs_check_delete();
}


std::unordered_map<std::string,std::string> bayinf::Graph::prior_sample() {
    std::uniform_real_distribution<double> dis(0,1);
    std::unordered_map<std::string,std::string> sample;

    for (auto& node : node_list) {
        unsigned int states_index = 0;
        if (!node.getParents().empty()) { // not a root node
            // retrieve the index to access the correct probabilities in the CPT given all the parents states (the current evidence)
            std::vector<unsigned int> parent_nstates;
            for (const std::string& parent : node.getParents()) {
                parent_nstates.push_back(node_list[node_indexes[parent]].getStates().size());
            }
            for (int i = 0; i < node.getParents().size(); i++) {
                unsigned int prod = 1;
                for (int j = i+1; j < node.getParents().size(); j++) {
                    prod *= parent_nstates[j];
                }
                states_index += node_list[node_indexes[node.getParents()[i]]].getStatesMap()[sample[node.getParents()[i]]] * prod;
            }
        }
        // now, based on the evidence, I want to access the right probabilities
        std::vector<float> cond_probs = node.getProbabilities()[states_index];

        float rand = dis(gen); // generate random number [0,1)
        for (int i = 0; i < cond_probs.size(); i++) { // I know that I have a probability for each state
            if (rand < cond_probs[i]) {
                sample[node.getName()] = node.getStates()[i]; // sample state from the distribution of the node
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
    for (auto& node : node_list) {
        unsigned int states_index = 0;

        bool is_evidence = false;
        for (auto& e : evidence) {
            if (e.first == node.getName()) {
                is_evidence = true;
                sample[node.getName()] = e.second;
                break;
            }
        }

        if (!node.getParents().empty()) { // not a root node
            // retrieve the index to access the correct probabilities in the CPT given all the parents states (the current evidence)
            std::vector<unsigned int> parent_nstates;
            for (const std::string& parent : node.getParents()) {
                parent_nstates.push_back(node_list[node_indexes[parent]].getStates().size());
            }
            for (int i = 0; i < node.getParents().size(); i++) {
                unsigned int prod = 1;
                for (int j = i+1; j < node.getParents().size(); j++) {
                    prod *= parent_nstates[j];
                }
                states_index += node_list[node_indexes[node.getParents()[i]]].getStatesMap()[sample[node.getParents()[i]]] * prod;
            }
        }
        // now, based on the evidence, I want to access the right probabilities
        std::vector<float> cond_probs = node.getProbabilities()[states_index];
        if (is_evidence) {
            w *= cond_probs[node.getStatesMap()[sample[node.getName()]]];
        } else {
            float rand = dis(gen); // generate random number [0,1)
            for (int i = 0; i < cond_probs.size(); i++) { // I know that I have a probability for each state
                if (rand < cond_probs[i]) {
                    sample[node.getName()] = node.getStates()[i]; // sample state from the distribution of the node
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
    std::vector<float> posteriors(node_list[node_indexes[query_variable]].getStates().size(), 0);

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
        posteriors[node_list[node_indexes[query_variable]].getStatesMap()[sample[query_variable]]]++;
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
    std::vector<float> posteriors(node_list[node_indexes[query_variable]].getStates().size(), 0);

    for (const std::string& ev : evidence_variables) {
        std::vector<std::string> tok = Utils::split_string(ev, '=');
        evidence_states[tok[0]] = tok[1];
    }

    /*// single thread version
    for (int i = 0; i < num_samples; i++) {
        std::tuple<std::unordered_map<std::string,std::string>, float> sample_weight = weighted_sample(evidence_states);
        std::unordered_map<std::string,std::string> sample = std::get<0>(sample_weight);
        float w = std::get<1>(sample_weight);

        posteriors[node_list[node_indexes[query_variable]]->getStatesMap()[sample[query_variable]]] += w;
    }*/

    int n_thread = (int)std::thread::hardware_concurrency() - 1; // TO FIGURE OUT
    int iterations = num_samples / n_thread;
    int left = num_samples % n_thread;

    auto t_fun = [&](int iterations) {
        std::vector<float> local_posteriors(node_list[node_indexes[query_variable]].getStates().size(), 0);
        for (int i = 0; i < iterations; i++) {
            std::tuple<std::unordered_map<std::string,std::string>, float> sample_weight = weighted_sample(evidence_states);
            std::unordered_map<std::string,std::string> sample = std::get<0>(sample_weight);
            float w = std::get<1>(sample_weight);
            local_posteriors[node_list[node_indexes[query_variable]].getStatesMap()[sample[query_variable]]] += w;
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
        posterior = round(posterior * 100.0)/100.0; // round it to 2 decimals
    }

    return posteriors;
}


#include "bayinf/Graph.h"
#include <iostream>
#include <string>
#include <random>
#include <future>
#include "tinyxml2.h"
#include "Utils.h"

//Define the static member
std::unordered_map<std::string, std::shared_ptr<std::vector<std::vector<float>>>> Node::probs_hashmap;

baynet::Graph::Graph(const std::string &filename)
{
    tinyxml2::XMLDocument doc;
    try {
        tinyxml2::XMLError err_id = doc.LoadFile(("../../" + filename).c_str());
        if (err_id != 0) {
            throw std::runtime_error((const char*)(err_id));
        }

        tinyxml2::XMLElement* root = doc.FirstChildElement("smile")->FirstChildElement("nodes" );

        // iterate over all the 'nodes' tags
        for (tinyxml2::XMLElement* e = root->FirstChildElement( ); e != nullptr; e = e->NextSiblingElement()) {
            if (strcmp(e->Name(), "cpt") == 0 || strcmp(e->Name(), "deterministic") == 0) {
                const char* node_id;
                e->QueryStringAttribute("id", &node_id);

                // save the states
                std::unordered_map<std::string, int> states_map;
                std::vector<std::string> states;

                for (tinyxml2::XMLElement* state = e->FirstChildElement("state" ); state != nullptr; state = state->NextSiblingElement("state"))
                {
                    const char* state_id;
                    state->QueryStringAttribute("id", &state_id);
                    states_map[state_id] = (int)states.size();
                    states.emplace_back(state_id);
                }

                std::vector<std::string> parents;
                std::vector<unsigned int> parent_wstates;
                if (e->FirstChildElement("parents") != nullptr) {
                    const char* parentlist = e->FirstChildElement("parents")->GetText();
                    for (const std::string& parent : utils::split_string(parentlist, ' ')) {
                        parents.push_back(parent);
                        parent_wstates.push_back(node_list[node_indexes[parent]].get_states().size());
                    }
                }

                // calculates parent weight (used for indexing the cpt during inference)
                for (int i = 0; i < parent_wstates.size(); i++) {
                    unsigned int prod = 1;
                    for (int j = i+1; j < parent_wstates.size(); j++) {
                        prod *= parent_wstates[j];
                    }
                    parent_wstates[i] = prod;
                }

                std::string hashedCPT;
                if (strcmp(e->Name(), "cpt") == 0) {
                    // save the probabilities
                    if (e->FirstChildElement("probabilities") != nullptr) {
                        std::string problist = e->FirstChildElement("probabilities")->GetText();
                        int n = 0;
                        size_t row_length = states.size();
                        size_t n_rows = utils::word_count(problist) / row_length;

                        //if hash(probabilities) is not in probs_hashmap, then add it,
                        // else make the probabilities pointer point the one already existing
                        hashedCPT = Node::hash_fun(problist);
                        std::vector<std::vector<float>> probabilities(n_rows);
                        //If the hashmap does not contain the node, then:
                        if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end())
                        {
                            for (auto& p : utils::split_string(problist, ' ')) {
                                probabilities[n / row_length].push_back(std::stof(p));
                                n++;
                            }
                            Node::probs_hashmap[hashedCPT] = std::make_shared<std::vector<std::vector<float>>>(probabilities);
                        }
                    }
                } else if (strcmp(e->Name(), "deterministic") == 0) {
                    // save the resulting states
                    if (e->FirstChildElement("resultingstates") != nullptr) {
                        std::string statelist = e->FirstChildElement("resultingstates")->GetText();
                        int n_rows = utils::word_count(statelist);
                        std::vector<std::vector<float>> probabilities(n_rows); // initialize num of rows
                        int n_states = 0;

                        //if hash(probabilities) is not in probs_hashmap, then add it,
                        // else make the probabilities pointer point the one already existing

                        hashedCPT = Node::hash_fun(statelist);

                        //If the hashmap does not contain the node, then:
                        if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end())
                        {
                            std::vector<std::vector<float>> table;
                            for (auto& res_state : utils::split_string(statelist, ' ')) {
                                std::vector<float> row(n_rows, 0);
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
                    }
                }
                //let's create the node and let's assign to it the probabilities added in probs_hashmap.
                Node node(node_id, states, states_map, Node::probs_hashmap[hashedCPT], parents, hashedCPT, parent_wstates);
                node_list.push_back(node);
                node_indexes[node_id] = (int)node_list.size() - 1;
            }
        }

    } catch (tinyxml2::XMLError err) { // catch error when loading the xdsl file
        std::cout << "LoadFile failed with errorID: " << err << "\n";
        exit(-1);
    }
}

void baynet::Graph::print_node(const std::string& name){
    const auto & n = node_list[node_indexes[name]];
    std::cout << "----------Node: " << n.get_name() << "----------" << std::endl;
    std::cout<<"Parents: ";

    for(auto& par : n.get_parents()) std::cout << par << " ";
    std::cout<<std::endl;

    std::cout<<"States: ";
    for(auto& st : n.get_states()) std::cout << st << " ";
    std::cout<<std::endl;

    std::cout << "Hashed CPT: " << n.get_hashed_cpt() << std::endl;


    std::cout<<"CPT count: "<<n.use_count()<<std::endl;
    std::cout<<"CPT:";
    for (const auto& row : n.value()) {
        std::cout<<std::endl;
        for (auto& el : row) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<"-------------------------"<< std::endl;
}


void baynet::Graph::edit_cpt(const std::string &name, const std::string &problist) {
    for (auto& node : node_list) {
        if (node.get_name() == name) {
            int cpt_size = utils::calc_cpt_size(*node.prob());
            if (cpt_size == utils::word_count(problist)) { // the size of the probability list must be the same as the cpt size
                int n = 0;
                int row_length = node.get_states().size();
                int n_rows = cpt_size / row_length;
                std::vector<std::vector<float>> probabilities(n_rows);
                for (auto& p : utils::split_string(problist, ' ')) {
                    probabilities[n / row_length].push_back(std::stof(p));
                    n++;
                }
                std::string oldHash = node.get_hashed_cpt(); // retrieve hashedCPT before modifying it
                std::string hashedCPT = Node::hash_fun(problist);
                if( Node::probs_hashmap.find(hashedCPT) == Node::probs_hashmap.end()) {
                    Node::probs_hashmap[hashedCPT] = std::make_shared<std::vector<std::vector<float>>>(probabilities);
                }
                node.set_probabilities(Node::probs_hashmap[hashedCPT], hashedCPT);
                Node::probs_check_delete(oldHash);
            }
            break;
        }
    }
}

std::unordered_map<std::string,std::string> baynet::Graph::prior_sample() {
    std::uniform_real_distribution<double> dis(0,1);
    std::unordered_map<std::string,std::string> sample;

    for (auto& node : node_list) {
        unsigned int states_index = 0;
        if (!node.get_parents().empty()) { // not a root node
            // retrieve the index to access the correct probabilities in the CPT given all the parents states (the current evidence)
            std::vector<unsigned int> parent_weight = node.get_parent_weight_states();
            for (int i = 0; i < node.get_parents().size(); i++) {
                states_index += node_list[node_indexes[node.get_parents()[i]]].get_states_map()[sample[node.get_parents()[i]]] * parent_weight[i];
            }
        }
        // now, based on the evidence, I want to access the right probabilities
        auto f = *node.prob();
        std::vector<float> cond_probs = f[states_index];

        float rand = dis(gen); // generate random number [0,1)
        for (int i = 0; i < cond_probs.size(); i++) { // I know that I have a probability for each state
            if (rand < cond_probs[i]) {
                sample[node.get_name()] = node.get_states()[i]; // sample state from the distribution of the node
                break;
            }
            rand -= cond_probs[i];
        }
    }
    return sample;
}

std::tuple<std::unordered_map<std::string,std::string>, float> baynet::Graph::weighted_sample(const std::unordered_map<std::string, std::string>& evidence) {
    std::uniform_real_distribution<double> dis(0,1);
    std::unordered_map<std::string,std::string> sample;
    float w = 1;
    for (auto& node : node_list) {
        unsigned int states_index = 0;

        bool is_evidence = false;
        for (auto& e : evidence) {
            if (e.first == node.get_name()) {
                is_evidence = true;
                sample[node.get_name()] = e.second;
                break;
            }
        }

        if (!node.get_parents().empty()) { // not a root node
            // retrieve the index to access the correct probabilities in the CPT given all the parents states (the current evidence)
            std::vector<unsigned int> parent_weight = node.get_parent_weight_states();
            for (int i = 0; i < node.get_parents().size(); i++) {
                states_index += node_list[node_indexes[node.get_parents()[i]]].get_states_map()[sample[node.get_parents()[i]]] * parent_weight[i];
            }
        }
        // now, based on the evidence, I want to access the right probabilities
        auto f = *node.prob();
        std::vector<float> cond_probs = f[states_index];
        if (is_evidence) {
            w *= cond_probs[node.get_states_map()[sample[node.get_name()]]];
        } else {
            float rand = dis(gen); // generate random number [0,1)
            for (int i = 0; i < cond_probs.size(); i++) { // I know that I have a probability for each state
                if (rand < cond_probs[i]) {
                    sample[node.get_name()] = node.get_states()[i]; // sample state from the distribution of the node
                    break;
                }
                rand -= cond_probs[i];
            }
        }
    }
    return std::make_tuple(sample, w);
}

std::vector<float> baynet::Graph::rejection_sampling(const std::string& query, int num_samples) {
    int exc=0;
    std::vector<std::string> tokens = utils::split_string(query, '|');
    std::string query_variable = tokens[0];
    if (check_query_validity(query_variable) == 1)
    {
        //std::cerr<<"Invalid query name.\n";
        throw "Invalid query name.\n";
    }
    else {
        std::vector<std::string> evidence_variables = utils::split_string(tokens[1], ',');
        for (const std::string& evidence: evidence_variables)
            if (check_query_validity(utils::split_string(evidence, '=')[0]) == 1) exc = 1;

        if (exc == 1) {
            //std::cerr << "Invalid evidence name.\n";
            throw "Invalid evidence name.\n";
        } else {

            std::unordered_map<std::string, std::string> evidence_states;
            std::vector<float> posteriors(node_list[node_indexes[query_variable]].get_states().size(), 0);

            for (const std::string &ev: evidence_variables) {
                std::vector<std::string> tok = utils::split_string(ev, '=');
                evidence_states[tok[0]] = tok[1];
            }

            int n_thread = (int) std::thread::hardware_concurrency() - 1;
            int iterations = num_samples / n_thread;
            int left = num_samples % n_thread;

            auto t_fun = [&](int iterations) {
                std::vector<float> local_posteriors(node_list[node_indexes[query_variable]].get_states().size(), 0);
                for (int i = 0; i < iterations; i++) {
                    std::unordered_map<std::string, std::string> sample = prior_sample();

                    // count only the samples that are consistent with the evidence
                    bool consistent = true;
                    for (auto &m: evidence_states) {
                        if (sample[m.first] != m.second)
                            consistent = false;
                    }
                    if (!consistent)
                        continue;

                    // posteriors[index of state that has been sampled for this query variable]
                    local_posteriors[node_list[node_indexes[query_variable]].get_states_map()[sample[query_variable]]]++;
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

            for (auto &res: t_results) {
                std::vector<float> loc_posteriors = res.get();
                for (int i = 0; i < posteriors.size(); i++)
                    posteriors[i] += loc_posteriors[i];
            }

            return utils::normalize(posteriors);
        }
    }
}

std::vector<float> baynet::Graph::likelihood_weighting(const std::string& query, int num_samples) {
    int exc = 0;
    std::vector<std::string> tokens = utils::split_string(query, '|');
    std::string query_variable = tokens[0];
    if (check_query_validity(query_variable) == 1)
    {
        //std::cerr<<"Invalid query name.\n";
        throw "Invalid query name.\n";
    }
    else {
        std::vector<std::string> evidence_variables = utils::split_string(tokens[1], ',');

        for (const std::string& evidence: evidence_variables)
            if (check_query_validity(utils::split_string(evidence, '=')[0]) == 1) exc = 1;

        if (exc == 1) {
            //std::cerr << "Invalid evidence name.\n";
            throw "Invalid evidence name.\n";
        } else {
            std::unordered_map<std::string, std::string> evidence_states;
            std::vector<float> posteriors(node_list[node_indexes[query_variable]].get_states().size(), 0);

            for (const std::string &ev: evidence_variables) {
                std::vector<std::string> tok = utils::split_string(ev, '=');
                evidence_states[tok[0]] = tok[1];
            }

            int n_thread = (int) std::thread::hardware_concurrency() - 1;
            int iterations = num_samples / n_thread;
            int left = num_samples % n_thread;

            auto t_fun = [&](int iterations) {
                std::vector<float> local_posteriors(node_list[node_indexes[query_variable]].get_states().size(), 0);
                for (int i = 0; i < iterations; i++) {
                    std::tuple<std::unordered_map<std::string, std::string>, float> sample_weight = weighted_sample(
                            evidence_states);
                    std::unordered_map<std::string, std::string> sample = std::get<0>(sample_weight);
                    float w = std::get<1>(sample_weight);
                    local_posteriors[node_list[node_indexes[query_variable]].get_states_map()[sample[query_variable]]] += w;
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

            for (auto &res: t_results) {
                std::vector<float> loc_posteriors = res.get();
                for (int i = 0; i < posteriors.size(); i++)
                    posteriors[i] += loc_posteriors[i];
            }

            return utils::normalize(posteriors);
        }
    }
}

std::vector<float> baynet::Graph::forward_sampling(const std::string& query, int num_samples) {
    std::vector<float> posteriors(node_list[node_indexes[query]].get_states().size(), 0);
    int n_thread = (int) std::thread::hardware_concurrency() - 1;
    int iterations = num_samples / n_thread;
    int left = num_samples % n_thread;

    auto t_fun = [&](int iterations) {
        std::vector<float> local_posteriors(node_list[node_indexes[query]].get_states().size(), 0);
        for (int i = 0; i < iterations; i++) {
            std::unordered_map<std::string, std::string> sample = prior_sample();
            // posteriors[index of state that has been sampled for this query variable]
            local_posteriors[node_list[node_indexes[query]].get_states_map()[sample[query]]]++;
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

    for (auto &res: t_results) {
        std::vector<float> loc_posteriors = res.get();
        for (int i = 0; i < posteriors.size(); i++)
            posteriors[i] += loc_posteriors[i];
    }

    return utils::normalize(posteriors);
}

int baynet::Graph::check_query_validity(const std::string& s){
    for(auto &v : node_list){
        if(v.get_name() == s) return 0;
    }
    return 1;
}

std::unordered_map<std::string, std::vector<float>> baynet::Graph::inference(int num_samples, const std::string& evidence, int algorithm) {
    std::unordered_map<std::string, std::vector<float>> results;

    for (auto& node : node_list) {
        try {
            std::string query;
            std::vector<float> posteriors;

            if (evidence.empty()) {
                query = node.get_name();
                posteriors = forward_sampling(query, num_samples);
            } else {
                query = node.get_name() + "|" + evidence;
                // if someone wants to add support for more algorithms in the future, he can just insert them here (maybe with a switch case)
                if (algorithm == 0) {
                    posteriors = likelihood_weighting(query, num_samples);
                } else {
                    posteriors = rejection_sampling(query, num_samples);
                }
            }
            results[query] = posteriors;
        } catch (const char* msg) {
            std::cerr << "Error: " << msg;
            break;
        }
    }

    return results;
}

void baynet::Graph::pretty_print(const std::unordered_map<std::string, std::vector<float>>& map) {
    for (auto& el : map) {

        std::cout << "P(" << el.first << ") = <";
        for (int i = 0; i < el.second.size()-1; i++)
            std::cout << el.second[i] << ",";
        std::cout << el.second[el.second.size()-1] << ">;\n";
    }
    std::cout << "\n";
};

void baynet::Graph::pretty_print_query(std::unordered_map<std::string, std::vector<float>> results, std::string query){
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


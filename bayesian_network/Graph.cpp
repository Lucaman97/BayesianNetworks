#include "Graph.h"
#include <iostream>
#include <string>
#include <sstream>

Graph::Graph(const std::string &filename) {
    tinyxml2::XMLDocument doc;
    try {
        tinyxml2::XMLError err_id = doc.LoadFile(("../bayesian_network/" + filename).c_str());
        if (err_id != 0) {
            throw err_id;
        }

        tinyxml2::XMLElement* root = doc.FirstChildElement("smile")->FirstChildElement("nodes" );

        // iterate over all the 'cpt' xml tags
        for (tinyxml2::XMLElement* e = root->FirstChildElement("cpt" ); e != nullptr; e = e->NextSiblingElement("cpt")) {
            const char* node_id;
            e->QueryStringAttribute("id", &node_id);

            // iterate over all states
            std::vector<std::string> states;
            for (tinyxml2::XMLElement* state = e->FirstChildElement("state" ); state != nullptr; state = state->NextSiblingElement("state")) {
                const char* state_id;
                e->QueryStringAttribute("id", &state_id);
                states.emplace_back(state_id);
            }

            // save the parents
            std::vector<std::string> parents;
            if (e->FirstChildElement("parents") != nullptr) {
                const char* parentlist = e->FirstChildElement("parents")->GetText();
                // metodo veloce trovato online per iterare le parole di una stringa
                std::istringstream ss(parentlist);
                std::string parent;
                while (ss >> parent) {
                    parents.push_back(parent);
                }
            }

            // save the probabilities
            std::vector<float> probabilities;
            if (e->FirstChildElement("probabilities") != nullptr) {
                const char* problist = e->FirstChildElement("probabilities")->GetText();
                std::istringstream ss(problist);
                std::string prob;
                while (ss >> prob) {
                    probabilities.push_back(std::stof(prob));
                }
            }

            create_node(node_id, std::make_shared<Node>(node_id, states, probabilities, parents));

            for (const std::string& parent : parents) {
                create_edge(parent, node_id);
            }
        }

        // in alcuni modelli ci sono nodi chiamati 'deterministic' oltre ai 'cpt' (Animals). Chiedere al prof se considerare anche quelli oppure assumere
        // che in input si avranno solo tag 'cpt'

    } catch (tinyxml2::XMLError err) { // catch error when loading the xdsl file
        std::cout << "LoadFile failed with errorID: " << err << "\n";
        exit(-1);
    }
}

void Graph::create_node(const std::string& name, const std::shared_ptr<Node>& cpt) {
    adj_list[name].push_back(cpt);
}

void Graph::create_edge(const std::string &from, const std::string &to) {
    adj_list[from].push_back(adj_list[to].front());
}

std::shared_ptr<Node> Graph::getNode(const std::string& name) {
    return adj_list[name].front();
}

std::ostream &operator<<(std::ostream &out, const Graph &graph) {
    bool first;
    for (const auto & row : graph.adj_list) {
        first = true;
        if (row.second.size() > 1) { // don't print sink node
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
}

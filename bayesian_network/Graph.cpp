#include "Graph.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> Graph::tokenize(std::string const &str, const char delim) {
    std::vector<std::string> out = {};
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
    return out;
}

Graph::Graph(const std::string &xdsl){
    //Aprire il file xdsl e parsarne il contenuto
    //std::fstream file;
    //file.open(gino);

    //carico il file su 'doc'
    //Per utilizzare TinyXML guardare https://tinyxml2.docsforge.com/
    // https://tinyxml2.docsforge.com/master/examples/#read-attributes-and-text-information
    // Esempio qua: https://gist.github.com/felton/5530029
    tinyxml2::XMLDocument doc;
    doc.Parse((xdsl).c_str());

    tinyxml2::XMLHandle docHandle(&doc);

    try {
        tinyxml2::XMLError err_id = doc.LoadFile(("../bayesian_network/" + xdsl).c_str());
        if (err_id != 0) {
            throw err_id;
        }
        tinyxml2::XMLNode *root = docHandle.FirstChildElement("smile").FirstChildElement("nodes").ToNode();

        //Itero sui nodi "cpt"
        for(tinyxml2::XMLNode *node = root->FirstChildElement("cpt"); node; node = node->NextSibling()) {

            std::string cptId = node->ToElement()->Attribute("id");


            //Aggiungo il nodo al grafo
            create_node(cptId.c_str());

            //Itero sui sottonodi "state"
            tinyxml2::XMLNode *state = node->FirstChildElement("state");
            for(; state != nullptr; state=state->NextSiblingElement("state")) {
                std::string stateId = state->ToElement()->Attribute("id");


                }

            //seleziono i nodi parenti
            tinyxml2::XMLElement *parents = node->FirstChildElement("parents");
            if(parents != nullptr){
                //Ogni ramo può avere più di un parente, itero su di essi
                for (std::string n: tokenize(parents->GetText(), ' ')) {
                    create_edge(n, cptId);
                }
            }


            tinyxml2::XMLElement *probs = node->FirstChildElement("probabilities");
            if(probs != nullptr) {
                //itero sulle probabilità
                for (std::string n: tokenize(probs->GetText(), ' ')) {
                    //aggiungere a cptable
                }
            }


            //auto lmao = root->FirstChildElement("probabilities")->ToElement()->GetText();

/*

            °*/
        }

    } catch (tinyxml2::XMLError err) { // catch error when loading the xdsl file
        std::cout << "LoadFile failed with errorID: " << err << "\n";
    }
}
void Graph::create_node(const std::string &name) {
    adj_list[name].push_back(std::make_shared<Node>(name));
}

void Graph::create_edge(const std::string &from, const std::string &to) {
    adj_list[from].push_back(adj_list[to].front());
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

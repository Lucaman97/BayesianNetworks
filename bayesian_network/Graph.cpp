#include "Graph.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>


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
        tinyxml2::XMLElement *entry = docHandle.FirstChildElement("smile").FirstChildElement("nodes").ToElement();


        const char *id;

        //doc.FirstChildElement("smile")->FirstChildElement("nodes" )->FirstChildElement("cpt" )->QueryStringAttribute("id", &id);


        //Itero sui nodi "cpt"
        for(tinyxml2::XMLNode *node = entry->FirstChildElement("cpt"); node; node = node->NextSibling()) {

            std::string cptId = node->ToElement()->Attribute("id");
            std::cout<<cptId<<std::endl;

            //Aggiungo il nodo al grafo
            create_node(cptId.c_str());

            //Itero sui sottonodi "state"
            //scrivere meglio il secondo elemento nell'inizializzazione del loop
            for(tinyxml2::XMLNode *subNode = node->FirstChildElement("state"); subNode->ToElement()->Attribute("id"); subNode= subNode->NextSibling()) {
                std::string cptId = subNode->ToElement()->Attribute("id");
                std::cout<<cptId<<std::endl;
            }

            //create_edge();

            /*
            const char *name = e->Attribute("name");
            if(name) std::cout<<name<<": ";

            std::cout<<e->GetText();

            int true_age = e->IntAttribute("age") + 50;

            std::cout<<" "<<true_age <<std::endl;
             */
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

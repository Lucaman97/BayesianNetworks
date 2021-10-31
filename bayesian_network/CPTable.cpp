//
// Created by lmann on 29/10/2021.
//
#include <iostream>
#include <fstream>
#include "CPTable.h"
#include "tinyxml2.h"
//Per utilizzare TinyXML guardare https://tinyxml2.docsforge.com/


CPTable::CPTable(const std::string& gino) {
    //Aprire il file xdsl e parsarne il contenuto
    //std::fstream file;
    //file.open(gino);

    //carico il file su 'doc'
    tinyxml2::XMLDocument doc;
    try {
        tinyxml2::XMLError err_id = doc.LoadFile(("../bayesian_network/" + gino).c_str());
        if (err_id != 0) {
            throw err_id;
        }
        //Bisogna capire che argomenti prende FirstChildElement(). Ad ora dà ancora errore.
        // Esempio qua: https://gist.github.com/felton/5530029

        // https://tinyxml2.docsforge.com/master/examples/#read-attributes-and-text-information
        const char *id;
        doc.FirstChildElement("smile")->FirstChildElement("nodes" )->FirstChildElement("cpt" )->QueryStringAttribute("id", &id);
        printf( "Name of first node: %s\n", id);

    } catch (tinyxml2::XMLError err) { // catch error when loading the xdsl file
        std::cout << "LoadFile failed with errorID: " << err << "\n";
    }
}
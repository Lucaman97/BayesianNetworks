//
// Created by lmann on 29/10/2021.
//
#include <iostream>
#include <fstream>
#include "CPTable.h"
#include "tinyxml2.h"
//Per utilizzare TinyXML guardare https://tinyxml2.docsforge.com/


CPTable::CPTable(std::string gino) {
    //Aprire il file xdsl e parsarne il contenuto
    std::fstream file;
    file.open(gino);

    //carico il file su 'doc'
    tinyxml2::XMLDocument doc;
    doc.LoadFile(gino.c_str());

    //Bisogna capire che argomenti prende FirstChildElement(). Ad ora dà ancora errore.
    // Esempio qua: https://gist.github.com/felton/5530029
    const char* title = doc.FirstChildElement( "nodes" )->FirstChildElement( "id" )->GetText();
    printf( "Name of play (1): %s\n", title );
}
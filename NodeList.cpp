#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    // TODO
    length = 0;
}

NodeList::~NodeList(){
    // TODO 
    
    for(int i = 0; i < getLength(); i++) {
        delete nodes[i];
    }

}

NodeList::NodeList(NodeList& other){
    // TODO
    for(int i = 0; i < getLength(); i++) {
        delete nodes[i];
    }

    for(int i = 0; i < other.getLength(); i++) {
        this->nodes[i] = new Node(*other.nodes[i]);
    }
    
}

int NodeList::getLength(){
    // TODO
    return this->length;
}

void NodeList::addElement(Node* newPos){
    // TODO
    if(getLength() < NODE_LIST_ARRAY_MAX_SIZE) {
        this->length++;
        //nodes = new Node*(newPos);
        this->nodes[getLength() - 1] = newPos;
    }
}

Node* NodeList::getNode(int i){
    // TODO
    return this->nodes[i];
}
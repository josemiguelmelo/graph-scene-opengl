//
//  Graph.h
//  CGFExample
//

#ifndef __CGFExample__Graph__
#define __CGFExample__Graph__

#include <stdio.h>
#include <vector>
#include "Node.h"
#include <string>



class Graph{
private:
    std::vector<Node *> * nodes;
    std::string rootid;
    
public:
    Graph(std::string rootid){
        this->rootid = rootid;
        this->nodes = new std::vector<Node *>();
    }
    
    std::vector<Node *> * getNodes(){ return this->nodes; }
    
    void addNode(Node * node){
        nodes->push_back(node);
    }
    
};


#endif /* defined(__CGFExample__Graph__) */

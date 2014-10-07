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
#include <map>



class Graph{
private:
    std::map<std::string, Node *> nodes;
    std::string rootid;
    
public:
    Graph(){
    }
    
    std::map<std::string, Node *>  getNodes(){ return this->nodes; }
    
    void addNode(Node * node){
        this->nodes[node->getID()] = node;
    }
    
    void setRootId(std::string rootid)
    {
        this->rootid = rootid;
    }
    
};


#endif /* defined(__CGFExample__Graph__) */

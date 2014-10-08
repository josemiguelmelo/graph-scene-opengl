//
//  Node.h
//  CGFExample
//
//  Created by José Melo on 07/10/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__Node__
#define __CGFExample__Node__

#include <stdio.h>
#include <vector>
#include <string>
#include "Transforms.h"
#include "Primitives.h"
#include <map>


class Node{
private:
    std::string id;
    std::string apperanceref;
    bool initialized;
    std::vector<Transforms *> * transforms;
    std::vector<Primitives *> * primitives;
    std::map<std::string, Node *> descendants;
    
public:
    
    Node(bool initialized){
        transforms=new std::vector<Transforms *>();
        primitives=new std::vector<Primitives *>();
        this->initialized=initialized;
    }
    
    std::string getID(){ return this->id; }
    std::string getAppearanceRef() { return this->apperanceref; }
    std::vector<Transforms *> * getTransforms(){ return this->transforms; }
    std::vector<Primitives *> * getPrimitives(){ return this->primitives; }
    std::map<std::string, Node*> getDescendants(){ return this->descendants; }
    
    void setID(std::string id){ this->id = id; }
    void setAppearanceRef(std::string appearanceref){ this->apperanceref = apperanceref; }
    void setTransforms(std::vector<Transforms *> * transforms){ this->transforms=transforms; }
    void setPrimitives(std::vector<Primitives *> * primitives) { this->primitives=primitives;}
    void addTransforms(Transforms * transform){ transforms->push_back(transform);}
    void addPrimitives(Primitives * primitive){ primitives->push_back(primitive);}
    void addDescendant(Node * node){ descendants[node->getID()]=node; }
    
    bool getInitialized() {
        return this->initialized;
    }
    
    void draw();
    
    
};

#endif /* defined(__CGFExample__Node__) */

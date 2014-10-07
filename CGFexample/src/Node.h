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


class Node{
private:
    std::string id;
    std::string apperanceref;
    std::vector<Transforms *> * transforms;
    std::vector<Primitives *> * primitives;
    std::vector<Node> * descendants;
    
public:
    
    Node(){
        transforms=new std::vector<Transforms *>();
        primitives=new std::vector<Primitives *>();
        descendants=new std::vector<Node>();
    }
    
    std::string getID(){ return this->id; }
    std::string getAppearanceRef() { return this->apperanceref; }
    std::vector<Transforms *> * getTransforms(){ return this->transforms; }
    std::vector<Primitives *> * getPrimitives(){ return this->primitives; }
    std::vector<Node> * getDescendants(){ return this->descendants; }
    
    void setID(std::string id){ this->id = id; }
    void setAppearanceRef(std::string appearanceref){ this->apperanceref = apperanceref; }
    void addTransforms(Transforms * transform){ transforms->push_back(transform);}
    void addPrimitives(Primitives * primitive){ primitives->push_back(primitive);}
    void addDescendant(Node node){ descendants->push_back(node); }
    
    
};

#endif /* defined(__CGFExample__Node__) */

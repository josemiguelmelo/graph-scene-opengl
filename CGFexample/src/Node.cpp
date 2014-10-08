//
//  Node.cpp
//  CGFExample
//
//  Created by José Melo on 07/10/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "Node.h"



void Node::draw(){
    glPushMatrix();
    for(int j = 0; j < transforms->size(); j++){
        transforms->at(j)->apply();
    }
    
    for(int i = 0; i < primitives->size(); i++){
        primitives->at(4)->draw();
    }
    
    glPopMatrix();
}
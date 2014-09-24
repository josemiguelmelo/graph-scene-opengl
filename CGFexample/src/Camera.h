//
//  Cameras.h
//  CGFExample
//
//  Created by José Melo on 23/09/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__Cameras__
#define __CGFExample__Cameras__


#include <stdio.h>
#include <string>

#include "CGFscene.h"
#include "CGFshader.h"


class Camera {
    
public:
    float background[4];
    std::string id;
    float near, far;
    
    float getBackground(int position) {return background[position];}
    std::string getID() {return id;}
    float getNear() {return near;}
    float getFar() {return far;}
    
    
};

class Ortho : public Camera{
public:
    float left, right, top, bottom;
    
    float getLeft() {return left;}
    float getRight() {return right;}
    float getTop() {return top;}
    float getBottom() {return bottom;}
    
    void setFar(float far) {this->far = far; }
    void setNear(float near) {this->near = near; }
    void setID(std::string id){this->id = id;}
    
    
};

class Perspective : public Camera{
public:
    float angle;
    float pos[3], target[3];
    
    float getAngle() {return angle;}
    float getPos(int position) {return pos[position];}
    float getTarget(int position) {return target[position];}
    
    
    
    void setFar(float far) {this->far = far; }
    void setNear(float near) {this->near = near; }
    void setID(std::string id){this->id = id;}
};



#endif


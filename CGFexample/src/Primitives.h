//
//  Primitives.h
//  CGFExample
//
//  Created by José Melo on 07/10/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__Primitives__
#define __CGFExample__Primitives__

#include <stdio.h>
#include <string>
#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFappearance.h"
#include <iostream>

class Primitives{
public:
    
    virtual std::string getType() = 0;
    virtual void draw() = 0;
};


class Rectangle : public Primitives{
private:
    float x1, y1;
    float x2, y2;
    
public:
    
    float getX1(){ return this->x1;}
    float getX2(){ return this->x2;}
    float getY1(){ return this->y1;}
    float getY2(){ return this->y2;}
    
    void setX1(float x1){ this->x1 = x1; }
    void setX2(float x2){ this->x2 = x2; }
    void setY1(float y1){ this->y1 = y1; }
    void setY2(float y2){ this->y2 = y2; }
    
    std::string getType() { return "rectangle"; }
    
    void draw();
};

class Triangle : public Primitives{
private:
    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
    
public:
    
    float getX1(){ return this->x1;}
    float getX2(){ return this->x2;}
    float getX3(){ return this->x3;}
    float getY1(){ return this->y1;}
    float getY2(){ return this->y2;}
    float getY3(){ return this->y3;}
    float getZ1(){ return this->z1;}
    float getZ2(){ return this->z2;}
    float getZ3(){ return this->z3;}
    
    void setX1(float x1){ this->x1 = x1; }
    void setX2(float x2){ this->x2 = x2; }
    void setX3(float x3){ this->x3 = x3; }
    void setY1(float y1){ this->y1 = y1; }
    void setY2(float y2){ this->y2 = y2; }
    void setY3(float y3){ this->y3 = y3; }
    void setZ1(float z1){ this->z1 = z1; }
    void setZ2(float z2){ this->z2 = z2; }
    void setZ3(float z3){ this->z3 = z3; }

    std::string getType() { return "triangle"; }
    
    
    void draw();
};

class Cylinder : public Primitives{
private:
    float base, top, height;
    int slices, stacks;
public:
    float getBase(){ return this->base; }
    float getTop(){ return this->top; }
    float getHeight(){ return this->height; }
    int getSlices(){ return this->slices; }
    int getStacks(){ return this->stacks; }
    
    void setBase(float base){ this->base = base; }
    void setTop(float top){ this->top = top; }
    void setHeight(float height){ this->height = height; }
    void setSlices(int slices){ this->slices = slices; }
    void setStacks(int stacks){ this->stacks = stacks; }
    std::string getType() { return "cylinder"; }
    
    
    void draw();

};

class Sphere : public Primitives{
private:
    float radius;
    int slices, stacks;
public:
    float getRadius(){ return this->radius; }
    int getSlices(){ return this->slices; }
    int getStacks(){ return this->stacks; }
    
    void setRadius(float radius){ this->radius = radius; }
    void setSlices(int slices){ this->slices = slices; }
    void setStacks(int stacks){ this->stacks = stacks; }
    std::string getType() { return "sphere"; }
    
    
    
    void draw();
};

class Torus : public Primitives{
private:
    float inner, outer;
    int slices, loops;
    
public:
    float getInner(){ return this->inner; }
    float getOuter(){ return this->outer; }
    int getSlices(){ return this->slices; }
    int getLoops(){ return this->loops; }
    
    void setInner(float inner){ this->inner = inner; }
    void setOuter(float outer){ this->outer = outer; }
    void setSlices(int slices){ this->slices = slices; }
    void setLoops(int loops){ this->loops = loops; }
    std::string getType() { return "torus"; }
    
    
    
    
    void draw();
};






#endif /* defined(__CGFExample__Primitives__) */

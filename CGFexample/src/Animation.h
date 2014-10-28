//
//  Animation.h
//  CGFExample
//


#ifndef __CGFExample__Animation__
#define __CGFExample__Animation__

#include <stdio.h>
#include <string>
#include <vector>
#include "ControlPoint.h"

class Animation{
protected:
    std::string id;
    float span;
public:
    Animation(){}
    Animation(std::string id, float span){
        this->id = id;
        this->span=span;
    }
    
    void setId(std::string id){ this->id = id;}
    void setSpan(float span){ this->span = span; }
    
    std::string getId(){ return this->id; }
    float getSpan(){ return this->span; }
};


class LinearAnimation: public Animation{
private:
    std::vector<ControlPoint> controlPoints;
    
    
public:
    LinearAnimation(std::string id, float span){
        this->id = id;
        this->span = span;
    }
    
    void setControlPoints(std::vector<ControlPoint> controlPoints){ this->controlPoints = controlPoints;}
    
    std::vector<ControlPoint> getControlPoints(){ return this->controlPoints;}
    
    
    
};

class CircularAnimation: public Animation{
private:
    
public:
    
};

#endif /* defined(__CGFExample__Animation__) */

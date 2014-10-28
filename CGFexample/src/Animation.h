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
#include "math.h"

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
    float totalDistance;
    float partialTime;
    
public:
    LinearAnimation(std::string id, float span){
        this->id = id;
        this->span = span;
        totalDistance = 0;
        partialTime = 0;
    }
    
    void addControlPoint(ControlPoint controlPoint){ this->controlPoints.push_back(controlPoint); }
    
    void setControlPoints(std::vector<ControlPoint> controlPoints){ this->controlPoints = controlPoints;}
    
    std::vector<ControlPoint> getControlPoints(){ return this->controlPoints;}
    float getTotalDistance(){ return this->totalDistance; }
    float getPartialTime(){ return this->partialTime; }
    
    float distanceBetweenPoints(ControlPoint p1, ControlPoint p2){
        return sqrt( pow(p1.getX()-p2.getX() , 2) + pow(p1.getY() - p2.getY(), 2) + pow(p1.getZ() - p2.getZ(),2 ));
    }
    
    void calculateTotalDistance(){
        totalDistance = 0;
        for (int i = 0; i< controlPoints.size()-1; i++){
            totalDistance += distanceBetweenPoints(controlPoints.at(i), controlPoints.at(i+1));
        }
    }
    
    void calculatePartialTime(){
        partialTime = totalDistance / controlPoints.size();
    }
    
    
};

class CircularAnimation: public Animation{
private:
    
public:
    
};

#endif /* defined(__CGFExample__Animation__) */

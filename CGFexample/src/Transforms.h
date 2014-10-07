//
//  Transforms.h
//  CGFExample
//

#ifndef __CGFExample__Transforms__
#define __CGFExample__Transforms__

#include <stdio.h>

class Transforms{
    
    
};


class Translation : public Transforms
{
private:
    float x, y, z;
public:
    
    float getX(){ return this->x; }
    float getY(){ return this->y; }
    float getZ(){ return this->z; }
    
    void setX(float x){ this->x = x; }
    void setY(float y){ this->y = y; }
    void setZ(float z){ this->z = z; }
};



class Rotation : public Transforms{
private:
    char axis;
    float angle;
public:
    char getAxis() {return this->axis; }
    float getAngle() {return this->angle; }
    
    void setAxis(char axis) { this->axis = axis; }
    void setAngle(float angle) { this->angle = angle; }
};


class Scale : public Transforms{
private:
    float xFactor, yFactor, zFactor;
public:

    float getXFactor(){ return this->xFactor; }
    float getYFactor(){ return this->yFactor; }
    float getZFactor(){ return this->zFactor; }
    
    void setXFactor(float xFactor){ this->xFactor = xFactor; }
    void setYFactor(float yFactor){ this->yFactor = yFactor; }
    void setZFactor(float zFactor){ this->zFactor = zFactor; }

};


#endif /* defined(__CGFExample__Transforms__) */

#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Globals.h"
#include "Camera.h"

#include <vector>

class Scene : public CGFscene
{
public:
	void init();
    void initGlobals();
	void display();
	void update(unsigned long t);
	~Scene();
    
    Globals * getGlobals() {return globals;}
    std::vector<Camera *> getCameras() {return cameras;}
    
    
    
private:
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
    
    
    Globals * globals;
    vector<Camera *> cameras;

};

#endif
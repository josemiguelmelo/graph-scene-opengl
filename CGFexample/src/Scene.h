#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Globals.h"

class Scene : public CGFscene
{
public:
	void init();
    void initGlobals();
	void display();
	void update(unsigned long t);
	~Scene();
    
    Globals * getGlobals() {return globals;}
    
private:
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
    
    
    Globals * globals;

};

#endif
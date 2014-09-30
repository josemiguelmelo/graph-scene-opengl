#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Globals.h"
#include "Camera.h"

#include <vector>


#include "CGFinterface.h"

class Scene : public CGFscene
{
public:
	void init();
    void setGlobals();
    void setCameras();
	void display();
	void update(unsigned long t);
    void controlPanel();
	~Scene();
    
    Globals * getGlobals() {return globals;}
    std::vector<Camera *> * getCameras() { return cameras;}
    
    
    void setActiveCamera(Camera * camera);
    void showCamera();
    
private:
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
    
    Camera * activeCamera;
    
    Globals * globals;
    std::vector<Camera *> * cameras;

};

#endif
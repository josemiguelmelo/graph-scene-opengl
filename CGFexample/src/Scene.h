#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Globals.h"
#include "Camera.h"
#include "Graph.h"

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
    Graph * getGraph() { return graph; }
    Camera * getActiveCamera(){ return this->activeCamera; }
    std::vector<Camera *> * getCameras() { return cameras; }
    
    void setActiveCamera(Camera * camera);
    void showCamera();
    void drawGraph();
    
    
private:
	CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
	CGFshader* shader;
    
    Camera * activeCamera;
    
    Globals * globals;
    Graph * graph;
    std::vector<Camera *> * cameras;
    
    long frameCount;

};

#endif
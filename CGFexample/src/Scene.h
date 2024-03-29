#ifndef SCENE_H
#define SCENE_H

#include "CGFscene.h"
#include "CGFshader.h"
#include "Globals.h"
#include "Camera.h"
#include "Graph.h"
#include "Texture.h"
#include "Light.h"
#include <vector>
#include "Appearance.h"
#include "Animation.h"
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
    std::vector<Light *> * getLights() { return lights; }
    std::vector<CGFlight *> * getCGFLights(){ return this->cgfLights;}
    
    void setActiveCamera(Camera * camera);
    void showCamera();
    void drawGraph();
    
    void setTextures(std::map<std::string, Texture*> * textures){ this->textures = textures; }
    std::map<std::string, Texture *> * getTextures() {return this->textures;}
    
    void setAppearances(std::map<std::string, Appearance* >* appearances){ this->appearances = appearances;}
    std::map<std::string, Appearance *> * getAppearances(){ return this->appearances; }
    void activateLights();
    
    void setWired(bool wired){ this->wired=wired;}
    bool isWired(){ return this->wired;}
    
    
    void setAnimations(std::map<std::string, Animation*> * animations) { this->animations = animations; }
    std::map<std::string, Animation*> * getAnimations(){ return this->animations; }
    
private:
    CGFlight* light0;
	CGFobject* obj;
	CGFappearance* materialAppearance;
	CGFappearance* textureAppearance;
    CGFshader* shader;
    
    std::map<std::string, Texture *> * textures;
    std::map<std::string, Appearance *> * appearances;
    
    Camera * activeCamera;
    
    Globals * globals;
    Graph * graph;
    std::vector<Camera *> * cameras;
    std::vector<Light *> * lights;
    std::vector<CGFlight *> * cgfLights;
    
    std::map<std::string, Animation*> * animations;
    
    long frameCount;
    long lastMilis = 0;

    bool wired;
    
};

#endif
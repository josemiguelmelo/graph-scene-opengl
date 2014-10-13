#ifndef __CGFExample__TPInterface__
#define __CGFExample__TPInterface__

#include <stdio.h>

#include "CGFinterface.h"
#include "Scene.h"

class TPInterface : public CGFinterface{
    Scene * scene;
    std::vector<Camera *> * camerasVector;
public:
    TPInterface(Scene * scene);
    void initGUI();
    
    virtual void processGUI(GLUI_Control *ctrl);
    
    int camerasVar;
    
};

#endif /* defined(__CGFExample__TPInterface__) */

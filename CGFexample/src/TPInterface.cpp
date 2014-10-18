#include "TPInterface.h"
#include "Camera.h"
#include <iostream>



TPInterface::TPInterface(Scene * scene){
    this->scene = scene;
}

void TPInterface::initGUI(){
    /** MAIN PANEL */
    GLUI_Panel * panel=addPanel("Painel de Controlo");
    
    /** LIGHT PANEL ***/
    GLUI_Panel *camerasPanel = addPanelToPanel(panel, "Camaras", 1);
    GLUI_Panel *lightsPanel = addPanelToPanel(panel, "Luzes");
    
    GLUI_Listbox * camerasList = addListboxToPanel(camerasPanel, "Camaras", &camerasVar , 1);
    
    camerasVector = scene->getCameras();
    lightsVector = scene->getLights();
    
    for ( int i = 0; i< camerasVector->size(); i++){
        camerasList->add_item(i, camerasVector->at(i)->getID().c_str());
        if(strcmp(camerasVector->at(i)->getID().c_str(), scene->getActiveCamera()->getID().c_str()) == 0){
            camerasList->set_int_val(i);
        }
    }
    
    for ( int i = 0; i< lightsVector->size(); i++){
        char* temp_str = new char[lightsVector->at(i)->getId().length() + 1];
        strcpy(temp_str, lightsVector->at(i)->getId().c_str());
        if(lightsVector->at(i)->getEnabled()){
            lightsVar[i]=1;
        }
        else{
            lightsVar[i]=0;
        }
        addCheckboxToPanel(lightsPanel, temp_str, &lightsVar[i],0);
    }
    
}


void TPInterface::processGUI(GLUI_Control *ctrl){
    /** CAMERAS HANDLE **/
    scene->setActiveCamera(camerasVector->at(camerasVar));
    
    for(int i =0; i < lightsVector->size(); i++){
        if(lightsVar[i]){
            lightsVector->at(i)->setEnabled(true);
        }else{
            lightsVector->at(i)->setEnabled(false);
        }
    }
    scene->activateLights();
}



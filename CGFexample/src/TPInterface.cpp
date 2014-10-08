//
//  TPInterface.cpp
//  CGFExample
//
//  Created by José Melo on 30/09/14.
//  Copyright (c) 2014 me. All rights reserved.
//

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
    
    GLUI_Listbox * list = addListboxToPanel(camerasPanel, "Camaras", &camerasVar , 1);
    
    camerasVector = scene->getCameras();
    
    for ( int i = 0; i< camerasVector->size(); i++){
        list->add_item(i, camerasVector->at(i)->getID().c_str());
        if(strcmp(camerasVector->at(i)->getID().c_str(), scene->getActiveCamera()->getID().c_str()) == 0){
            list->set_int_val(i);
        }
    }
    
}


void TPInterface::processGUI(GLUI_Control *ctrl){
    /** CAMERAS HANDLE **/
    scene->setActiveCamera(camerasVector->at(camerasVar));
    
}



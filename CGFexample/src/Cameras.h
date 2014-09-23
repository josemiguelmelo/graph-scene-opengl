//
//  Cameras.h
//  CGFExample
//
//  Created by José Melo on 23/09/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#ifndef __CGFExample__Cameras__
#define __CGFExample__Cameras__


#include <stdio.h>
#include <string>

#include "CGFscene.h"
#include "CGFshader.h"


class Cameras {
    
public:
    float background[4];
    std::string mode, shading;
    
    GLenum getMode();
    GLenum getShading();
    
    float getBackground(int position);
    
    
};

#endif


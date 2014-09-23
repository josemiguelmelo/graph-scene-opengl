

#include "Globals.h"


GLenum Globals::getMode(){
    if(this->mode == "fill"){
        return GL_FILL;
    }else if(this->mode == "point"){
        return GL_POINT;
    }else if(this->mode == "line"){
        return GL_LINE;
    }
    throw "Not valid globals mode";
}

GLenum Globals::getShading(){
    if(this->shading == "flat"){
        return GL_FLAT;
    }else if(this->mode == "gourard"){
        return GL_SMOOTH;
    }
    throw "Not valid globals mode";
}

float Globals::getBackground(int position){
    return this->background[position];
}



GLenum Globals::getCulling(){
    if(this->face=="none"){
        return GL_FRONT;
    }
    else if(this->face == "back"){
        return GL_BACK;
    }else if(this->face == "front"){
        return GL_FRONT;
    }else if(this->face == "both"){
        return GL_FRONT_AND_BACK;
    }
    
}
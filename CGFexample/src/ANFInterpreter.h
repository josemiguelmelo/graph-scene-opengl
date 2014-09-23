#ifndef _ANFInterpreter_H_
#define _ANFInterpreter_H_

#include "tinyxml.h"

#include "Globals.h"
#include "Scene.h"

#include <string>
#include <iostream>

class ANFInterpreter
{
public:
	ANFInterpreter(char *filename, Scene * scene);
	~ANFInterpreter();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
	
protected:
    Scene * scene;
	TiXmlDocument* doc;

	TiXmlElement* globalsElement;
    
};

#endif
#ifndef _ANFInterpreter_H_
#define _ANFInterpreter_H_

#include "tinyxml.h"

#include "Globals.h"
#include "Scene.h"

#include <string>
#include <iostream>
#include <vector>

#include "Transforms.h"
#include "Primitives.h"

class ANFInterpreter
{
public:
	ANFInterpreter(char *filename, Scene * scene);
	~ANFInterpreter();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
    
    void loadGraph();
    std::vector<Transforms *> * loadTransforms(TiXmlElement * transformsElements);
    std::vector<Primitives *> * loadPrimitives(TiXmlElement * primitivesElement);
    
protected:
    Scene * scene;
	TiXmlDocument* doc;
    
    TiXmlElement* globalsElement;
    TiXmlElement* camerasElement;
    TiXmlElement* graphElement;
    
};

#endif
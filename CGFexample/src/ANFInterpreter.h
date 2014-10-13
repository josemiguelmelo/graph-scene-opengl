#ifndef _ANFInterpreter_H_
#define _ANFInterpreter_H_

#include "tinyxml.h"

#include "Globals.h"
#include "Scene.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "Transforms.h"
#include "Primitives.h"

class ANFInterpreter
{
public:
	ANFInterpreter(char *filename, Scene * scene);
	~ANFInterpreter();

	static TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val);
    
    void loadGraph();
    void replaceEmptyNodes();
    std::map<std::string, Node*> * loadDescendants(TiXmlElement * descendantsElements);
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
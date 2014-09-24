#include "ANFInterpreter.h"

ANFInterpreter::ANFInterpreter(char *filename, Scene * scene)
{
    
    // Read XML from file
    this->scene = scene;
    
    doc=new TiXmlDocument( filename );
    bool loadOkay = doc->LoadFile();
    
    if ( !loadOkay )
    {
        printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
        exit( 1 );
    }
    
    TiXmlElement* anfScene= doc->FirstChildElement( "anf" );
    
    if (anfScene == NULL)
    {
        printf("Main anf block element not found! Exiting!\n");
        exit(1);
    }
    
    globalsElement = anfScene->FirstChildElement( "globals" );
    camerasElement = anfScene->FirstChildElement("cameras");
    
    Globals * globals = scene->getGlobals();
    std::vector<Camera *> cameras = scene->getCameras();
    
    // Init
    // An example of well-known, required nodes
    
    if (globalsElement == NULL)
    {
        printf("Globals block not found!\n");
    }
    else
    {
        printf("Processing globals:\n");
        // frustum: example of a node with individual attributes
        TiXmlElement* drawingElement=globalsElement->FirstChildElement("drawing");
        if (drawingElement)
        {
            std::string mode, shading;
            char *background = NULL;
            float r, g, b, alpha;
            mode = drawingElement->Attribute("mode");
            shading = drawingElement->Attribute("shading");
            background = (char * ) drawingElement->Attribute("background");
            globals->mode = mode;
            globals->shading = shading;
            
            sscanf(background, "%f %f %f %f", &r, &g, &b, &alpha);
            
            globals->background[0] = r;
            globals->background[1] = g;
            globals->background[2] = b;
            globals->background[3] = alpha;
            
            
        }
        else {
            printf("drawing not found\n");
        }
        
        
        TiXmlElement* cullingElement=globalsElement->FirstChildElement("culling");
        if(cullingElement){
            std::string face, order;
            face = cullingElement->Attribute("face");
            order = cullingElement->Attribute("order");
            globals->face = face;
            globals->order = order;
            
        }else{
            printf("culling not found");
        }
        
        TiXmlElement* lightingElement=globalsElement->FirstChildElement("lighting");
        if(lightingElement){
            std::string doublesided, local, enabled;
            char *ambientString = NULL;
            float r, g, b, alpha;
            float ambient[4];
            doublesided = lightingElement->Attribute("doublesided");
            local = lightingElement->Attribute("local");
            enabled = lightingElement->Attribute("enabled");
            ambientString = (char *) lightingElement->Attribute("ambient");
            
            sscanf(ambientString, "%f %f %f %f", &ambient[0], &ambient[1], &ambient[2], &ambient[3]);
            
            globals->doublesided = doublesided;
            globals->local = local;
            globals->enabled = enabled;
            globals->ambient[0] = ambient[0];
            globals->ambient[1] = ambient[1];
            globals->ambient[2] = ambient[2];
            globals->ambient[3] = ambient[3];
            
            
        }
    }
    
    /** GET CAMERAS **/
    
    if(camerasElement==NULL){
        printf("Cameras block not found!\n");
    }else{
        TiXmlElement * orthoElements = camerasElement->FirstChildElement("ortho");
        TiXmlElement * perspectiveElements = camerasElement->FirstChildElement("perspective");
        while(orthoElements){
            Ortho * ortho = new Ortho();
            ortho->right =(float)atof(orthoElements->Attribute("right"));
            ortho->left = (float)atof(orthoElements->Attribute("left"));
            ortho->top = (float)atof(orthoElements->Attribute("top"));
            ortho->bottom = (float)atof(orthoElements->Attribute("bottom"));
            ortho->setFar((float)atof(orthoElements->Attribute("far")));
            ortho->setNear((float)atof(orthoElements->Attribute("near")));
            ortho->setID(orthoElements->Attribute("id"));
            
            
            // armazenar nalguma estrutura de dados
            
            orthoElements = orthoElements->NextSiblingElement("ortho");
        }
        
        while(perspectiveElements){
            Perspective * persp = new Perspective();
            persp->angle =(float)atof(orthoElements->Attribute("angle"));
            
            char *posString = NULL;
            char *targetString = NULL;
            posString = (char *) perspectiveElements->Attribute("pos");
            targetString = (char *) perspectiveElements->Attribute("target");
            
            float pos[3];
            float target[3];
            sscanf(posString, "%f %f %f", &pos[0], &pos[1], &pos[2]);
            sscanf(targetString, "%f %f %f", &target[0], &target[1], &target[2]);
            
            persp->pos[0] = pos[0];
            persp->pos[1] = pos[1];
            persp->pos[2] = pos[2];
            persp->target[0] = target[0];
            persp->target[1] = target[1];
            persp->target[2] = target[2];
            
            persp->setFar((float)atof(orthoElements->Attribute("far")));
            persp->setNear((float)atof(orthoElements->Attribute("near")));
            persp->setID(perspectiveElements->Attribute("id"));
            
            perspectiveElements = perspectiveElements->NextSiblingElement("perspective");
        }
        
    }
    
    
}

ANFInterpreter::~ANFInterpreter()
{
    delete(doc);
}

//-------------------------------------------------------

TiXmlElement *ANFInterpreter::findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
    TiXmlElement *child=parent->FirstChildElement();
    int found=0;
    
    while (child && !found)
        if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
            found=1;
        else
            child=child->NextSiblingElement();
    
    return child;
}
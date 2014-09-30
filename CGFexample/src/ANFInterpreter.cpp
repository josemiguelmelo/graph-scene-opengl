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
    std::vector<Camera *> * cameras = scene->getCameras();
    
    cameras->size();
    
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
    std::string initialCameraId = camerasElement->Attribute("initial");
    if(camerasElement==NULL){
        printf("Cameras block not found!\n");
    }else{
        TiXmlElement * orthoElements = camerasElement->FirstChildElement("ortho");
        TiXmlElement * perspectiveElements = camerasElement->FirstChildElement("perspective");
        while(orthoElements){
            Ortho * orthogonalCamera = new Ortho();
            orthogonalCamera->right =(float)atof(orthoElements->Attribute("right"));
            orthogonalCamera->left = (float)atof(orthoElements->Attribute("left"));
            orthogonalCamera->top = (float)atof(orthoElements->Attribute("top"));
            orthogonalCamera->bottom = (float)atof(orthoElements->Attribute("bottom"));
            orthogonalCamera->setFar((float)atof(orthoElements->Attribute("far")));
            orthogonalCamera->setNear((float)atof(orthoElements->Attribute("near")));
            orthogonalCamera->setID(orthoElements->Attribute("id"));
            
            if(initialCameraId == orthogonalCamera->getID()) {
                scene->setActiveCamera(orthogonalCamera);
            }
            
            cameras->push_back(orthogonalCamera);
            
            orthoElements = orthoElements->NextSiblingElement("ortho");
        }
        
        while(perspectiveElements){
            Perspective * perspectiveCamera = new Perspective();
            perspectiveCamera->angle =(float)atof(perspectiveElements->Attribute("angle"));
            
            char *posString = NULL;
            char *targetString = NULL;
            posString = (char *) perspectiveElements->Attribute("pos");
            targetString = (char *) perspectiveElements->Attribute("target");
            
            float pos[3];
            float target[3];
            sscanf(posString, "%f %f %f", &pos[0], &pos[1], &pos[2]);
            sscanf(targetString, "%f %f %f", &target[0], &target[1], &target[2]);
            
            perspectiveCamera->pos[0] = pos[0];
            perspectiveCamera->pos[1] = pos[1];
            perspectiveCamera->pos[2] = pos[2];
            perspectiveCamera->target[0] = target[0];
            perspectiveCamera->target[1] = target[1];
            perspectiveCamera->target[2] = target[2];
            
            perspectiveCamera->setFar((float)atof(perspectiveElements->Attribute("far")));
            perspectiveCamera->setNear((float)atof(perspectiveElements->Attribute("near")));
            perspectiveCamera->setID(perspectiveElements->Attribute("id"));
            
            perspectiveElements = perspectiveElements->NextSiblingElement("perspective");

            if(initialCameraId == perspectiveCamera->getID()) {
                scene->setActiveCamera(perspectiveCamera);
            }
            
            if(cameras==NULL)
                cout << "null cameras";

            cameras->push_back(perspectiveCamera);
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
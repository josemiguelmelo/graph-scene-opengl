#include "ANFInterpreter.h"

void ANFInterpreter::loadGraph(){
    std::string rootid = graphElement->Attribute("rootid");
    
    TiXmlElement * nodeElements = graphElement->FirstChildElement("node");
    while(nodeElements){
        Node * node = new Node(true);
        std::string nodeID = nodeElements->Attribute("id");
        
        TiXmlElement * transformsElements = nodeElements->FirstChildElement("transforms");
        
        TiXmlElement * primitivesElements = nodeElements->FirstChildElement("primitives");
        
        node->setPrimitives(loadPrimitives(primitivesElements));
        node->setTransforms(loadTransforms(transformsElements));
        node->setID(nodeID);
        
        
        this->scene->getGraph()->addNode(node);
        
        nodeElements = nodeElements->NextSiblingElement();
    }

}

std::vector<Transforms *> * ANFInterpreter::loadTransforms(TiXmlElement * transformsElements) {
    std::vector<Transforms *> * transforms = new std::vector<Transforms*>();
    
    
    TiXmlElement * transformElement = transformsElements->FirstChildElement("transform");
    
    while(transformElement) {
        if(strcmp(transformElement->Attribute("type"), "translate") == 0){
            Translation * translation = new Translation();
            char* to = (char *)transformElement->Attribute("to");
            float x, y, z;
            sscanf(to, "%f %f %f", &x, &y, &z);
            
            translation->setX(x);
            translation->setY(y);
            translation->setZ(z);
            transforms->push_back(translation);
            cout << "here";
        }
        
        if(strcmp(transformElement->Attribute("type"),"rotate") == 0){
            Rotation * rotation = new Rotation();
            std::string axis = transformElement->Attribute("axis");
            
            char* angle_string = (char *)transformElement->Attribute("angle");
            float angle;
            sscanf(angle_string, "%f", &angle);
            
            rotation->setAngle(angle);
            rotation->setAxis(axis[0]);
            transforms->push_back(rotation);
            cout << "here1";
        }
        
        if(strcmp(transformElement->Attribute("type"),"scale") == 0){
            Scale * scale = new Scale();
            
            char* factor = (char *)transformElement->Attribute("factor");
            float x, y, z;
            sscanf(factor, "%f %f %f", &x, &y, &z);
            
            scale->setXFactor(x);
            scale->setYFactor(y);
            scale->setZFactor(z);
            transforms->push_back(scale);
        }
        
        
        transformElement = transformElement->NextSiblingElement("transform");
    }
    
    return transforms;

}

std::vector<Primitives *> * ANFInterpreter::loadPrimitives(TiXmlElement * primitivesElement) {
    std::vector<Primitives *> * primitives = new std::vector<Primitives *>();
    
    TiXmlElement * rectangleElement = primitivesElement->FirstChildElement("rectangle");
    
    while(rectangleElement) {
        Rectangle * rectangle = new Rectangle();
        char* xy1 = (char *)rectangleElement->Attribute("xy1");
        char* xy2 = (char *)rectangleElement->Attribute("xy2");
        
        float x1, y1, x2, y2;
        sscanf(xy1, "%f %f", &x1, &y1);
        sscanf(xy2, "%f %f", &x2, &y2);
        
        rectangle->setX1(x1);
        rectangle->setX2(x2);
        rectangle->setY1(y1);
        rectangle->setY2(y2);
        
        primitives->push_back(rectangle);
        rectangleElement = rectangleElement->NextSiblingElement("rectangle");
    }
    
    TiXmlElement * triangleElement = primitivesElement->FirstChildElement("triangle");
    
    while(triangleElement) {
        Triangle * triangle = new Triangle();
        char* xyz1 = (char *)triangleElement->Attribute("xyz1");
        char* xyz2 = (char *)triangleElement->Attribute("xyz2");
        char* xyz3 = (char *)triangleElement->Attribute("xyz3");
        
        float x1, y1, z1, x2, y2, z2, x3, y3, z3;
        sscanf(xyz1, "%f %f %f", &x1, &y1, &z1);
        sscanf(xyz2, "%f %f %f", &x2, &y2, &z2);
        sscanf(xyz3, "%f %f %f", &x3, &y3, &z3);
        
        triangle->setX1(x1);
        triangle->setX2(x2);
        triangle->setX3(x3);
        triangle->setY1(y1);
        triangle->setY2(y2);
        triangle->setY3(y3);
        triangle->setZ1(z1);
        triangle->setZ2(z2);
        triangle->setZ3(z3);
        
        primitives->push_back(triangle);
        triangleElement = triangleElement->NextSiblingElement("triangle");
    }
    
    
    
    TiXmlElement * cylinderElement = primitivesElement->FirstChildElement("cylinder");
    
    while(cylinderElement) {
        Cylinder * cylinder = new Cylinder();
        /** get cylinder parameters from ANF **/
        char* base_char = (char *)cylinderElement->Attribute("base");
        char* top_char = (char *)cylinderElement->Attribute("top");
        char* height_char = (char *)cylinderElement->Attribute("height");
        char* slices_char = (char *)cylinderElement->Attribute("slices");
        char* stacks_char = (char *)cylinderElement->Attribute("stacks");
        
        /** convert char parameters to correct types **/
        float base, top, height;
        int slices, stacks;
        sscanf(base_char, "%f", &base);
        sscanf(top_char, "%f", &top);
        sscanf(height_char, "%f", &height);
        slices = atoi(slices_char);
        stacks = atoi(stacks_char);
        /** set cylinder parameters **/
        cylinder->setBase(base);
        cylinder->setTop(top);
        cylinder->setHeight(height);
        cylinder->setSlices(slices);
        cylinder->setStacks(stacks);
        
        primitives->push_back(cylinder);
        cylinderElement = cylinderElement->NextSiblingElement("cylinder");
    }
    
    
    TiXmlElement * sphereElement = primitivesElement->FirstChildElement("sphere");
    
    while(sphereElement) {
        Sphere * sphere = new Sphere();
        /** get sphere parameters from ANF **/
        char* radius_char = (char *)sphereElement->Attribute("radius");
        char* slices_char = (char *)sphereElement->Attribute("slices");
        char* stacks_char = (char *)sphereElement->Attribute("stacks");
        
        /** convert char parameters to correct types **/
        float radius;
        int slices, stacks;
        sscanf(radius_char, "%f", &radius);
        slices = atoi(slices_char);
        stacks = atoi(stacks_char);
        
        /** set sphere parameters **/
        sphere->setRadius(radius);
        sphere->setSlices(slices);
        sphere->setStacks(stacks);
        
        primitives->push_back(sphere);
        sphereElement = sphereElement->NextSiblingElement("sphere");
    }
    
    TiXmlElement * torusElement = primitivesElement->FirstChildElement("torus");
    
    while(torusElement) {
        Torus * torus = new Torus();
        /** get sphere parameters from ANF **/
        char* inner_char = (char *)torusElement->Attribute("inner");
        char* outer_char = (char *)torusElement->Attribute("outer");
        char* slices_char = (char *)torusElement->Attribute("slices");
        char* loops_char = (char *)torusElement->Attribute("loops");
        
        /** convert char parameters to correct types **/
        float inner, outer;
        int slices, loops;
        sscanf(inner_char, "%f", &inner);
        sscanf(outer_char, "%f", &outer);
        slices = atoi(slices_char);
        loops = atoi(loops_char);
        
        /** set sphere parameters **/
        torus->setInner(inner);
        torus->setOuter(outer);
        torus->setSlices(slices);
        torus->setLoops(loops);
        
        primitives->push_back(torus);
        torusElement = torusElement->NextSiblingElement("torus");
    }
    
    return primitives;
    
}


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
    graphElement = anfScene->FirstChildElement("graph");
    
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
            orthogonalCamera->setDirection(orthoElements->Attribute("direction")[0]);
            
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
    
    loadGraph();
    
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
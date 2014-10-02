#include "Scene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "ExampleObject.h"

#include <math.h>

#include "CGFappearance.h"
#include "ANFInterpreter.h"


void Scene::setGlobals(){
    // drawing
    glPolygonMode(GL_FRONT_AND_BACK, globals->getMode());
    glClearColor(globals->getBackground(0), globals->getBackground(1), globals->getBackground(2),globals->getBackground(3));
    glEnable(globals->getShading());
    
    
    // culling
    if(globals->getCulling()!=-1){
        glEnable(GL_CULL_FACE);
        glCullFace(globals->getCulling());
        glFrontFace(globals->getOrder());
    }
    if(globals->isLightEnabled()==GL_TRUE){
        glEnable(GL_LIGHTING);
        glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, globals->isDoubleSided());
        glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, globals->isLocalLight());
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globals->getLightAmbient());  // Define ambient light
    }
}

void Scene::setCameras() {
    for(int i = 0; i < cameras->size(); i++) {
        cout << "mr camera: " << cameras->at(i)->getID() << typeid(cameras->at(i)).name() << std::endl;
        
        
        
    }
    
    
}


void Scene::init()
{
    cameras = new std::vector<Camera *>();
    
    globals = new Globals();
    char * anfPath = "/Users/josemiguelmelo/Documents/FEUP/LAIG/CGFlib-master/CGFexample/data/scene.xml";
    
    ANFInterpreter anfInterpreter = ANFInterpreter(anfPath, this);
    
    setGlobals();
    setCameras();
    
    
	// Enables lighting computations
	//glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, CGFlight::background_ambient);  // Define ambient light
	
	// Declares and enables a light
	float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();

	// Defines a default normal
	glNormal3f(0,0,1);

	obj=new ExampleObject();
	materialAppearance=new CGFappearance();
	textureAppearance=new CGFappearance("../data/pyramid.jpg",GL_REPEAT, GL_REPEAT);
	shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");

	setUpdatePeriod(30);
}


void Scene::setActiveCamera(Camera * camera) {
    activeCamera = camera;
    
}

void Scene::showCamera()
{
    if(activeCamera->getType() == "persp") {
        Perspective * perspCamera = (Perspective *) activeCamera;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluPerspective(perspCamera->getAngle(), 1, perspCamera->getNear(), perspCamera->getFar());
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(perspCamera->getPos(0), perspCamera->getPos(1), perspCamera->getPos(2), perspCamera->getTarget(0), perspCamera->getTarget(1), perspCamera->getTarget(2), 0.0f, 1.0f, 0.0f);
    }
    if(activeCamera->getType() == "ortho") {
        Ortho * orthoCamera = (Ortho *) activeCamera;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(orthoCamera->getLeft(), orthoCamera->getRight(), orthoCamera->getBottom(), orthoCamera->getTop(), orthoCamera->getNear(), orthoCamera->getFar());
        glMatrixMode(GL_MODELVIEW);
        switch (orthoCamera->getDirection()) {
            case 'x':
                break;
            case 'y':
                glRotated(90,0,0,1);
                break;
            case 'z':
                glRotated(-90,0,1,0);
            default:
                break;
        }
    }
}

void Scene::update(unsigned long t)
{
	shader->bind();
	shader->update(t/400.0);
	shader->unbind();
	
}
	
void Scene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	//CGFscene::activeCamera->applyView();
    showCamera();
    
	// Draw (and update) light
	light0->draw();

	// Draw axis
	axis.draw();


	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos

	// Simple object
	materialAppearance->apply();
	obj->draw();

	// textured object

	glTranslatef(0,4,0);
	textureAppearance->apply();
	obj->draw();

	// shader object

	glTranslatef(0,4,0);
	shader->bind();
	obj->draw();
	shader->unbind();

	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

Scene::~Scene()
{
	delete(shader);
	delete(textureAppearance);
	delete(materialAppearance);
	delete(obj);
	delete(light0);
}

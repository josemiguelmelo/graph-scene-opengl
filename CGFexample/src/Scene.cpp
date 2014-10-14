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

void Scene::init()
{
    frameCount = 0;
    cameras = new std::vector<Camera *>();
    
    globals = new Globals();
    graph = new Graph();
    char * anfPath = "/Users/josemiguelmelo/Documents/FEUP/3o Ano/LAIG/CGFlib-master/CGFexample/data/cena.anf";
    
    ANFInterpreter anfInterpreter = ANFInterpreter(anfPath, this);
    
    setGlobals();
    
    

    // Declares and enables a light
    float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
    float light1_pos[4] = {10.0, 10.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();
    
    light1 = new CGFlight(GL_LIGHT1, light1_pos);
    light1->enable();

	// Defines a default normal
	glNormal3f(0,0,1);

	obj=new ExampleObject();
    materialAppearance=new CGFappearance();
	shader=new CGFshader("../data/texshader.vert","../data/texshader.frag");

	setUpdatePeriod(30);
    
    for (std::map<std::string, Appearance*>::iterator it=appearances->begin(); it != appearances->end(); it++) {
        cout << "Appearance ID = " <<  it->second->getId() << endl;
    }
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
        gluPerspective(perspCamera->getAngle(), 1, perspCamera->getNear(), perspCamera->getFar());
     
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
                glRotated(90,0,1,0);
                glScaled(1,1,-1);
                break;
            case 'y':
                glRotated(90,1,0,0);
                glScaled(1,-1,1);
                break;
            case 'z':
                break;
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
	CGFscene::activeCamera->applyView();
    //showCamera();
    
	// Draw (and update) light
	light0->draw();
    light1->draw();

	// Draw axis
	axis.draw();
	// ---- END Background, camera and axis setup
    
    GLfloat identityMatrix[4][4];
    glGetFloatv(GL_MODELVIEW_MATRIX, &identityMatrix[0][0]);
    
    cout << textures->at(appearances->begin()->second->getTextureRef())->getFile();
    appearances->begin()->second->apply();
    graph->getNodes()->at(graph->getRootId())->draw(identityMatrix);
    
	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
    
    //cout << frameCount << endl;
    frameCount++;
}

Scene::~Scene()
{
	delete(shader);
	delete(textureAppearance);
	delete(materialAppearance);
	delete(obj);
	delete(light0);
}

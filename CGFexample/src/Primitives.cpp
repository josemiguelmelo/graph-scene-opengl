#include "Primitives.h"
#include <cmath>


void Rectangle::draw(){

    glBegin(GL_QUADS);
    
    glNormal3f(x1, y1, 0);
    glTexCoord2d(0,0);
    glVertex3d(x1,y1,0);
    
    glTexCoord2d(1,0);
    glNormal3f(x2, y1, 0);
    glVertex3d(x2,y1,0);
    
    glTexCoord2d(1,1);
    glNormal3f(x2, y2, 0);
    glVertex3d(x2,y2,0);
    
    glTexCoord2d(0,1);
    glNormal3f(x1, y2, 0);
    glVertex3d(x1,y2,0);
        
    glEnd();
}


void Triangle::draw(){
    
    glBegin(GL_TRIANGLES);
    // Lower left vertex
    glVertex3f(x1, y1, z1);
    // Lower right vertex
    glVertex3f( x2, y2, z2);
    // Upper vertex
    glVertex3f( x3,  y3, z3);
    glEnd();
    
    
}


void Cylinder::draw(){
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    gluCylinder(quadratic,
                this->base,
                this->top,
                this->height,
                this->slices,
                this->stacks);
    
}



void Sphere::draw(){
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluQuadricTexture(quadratic, true);
    gluSphere(quadratic,
                this->radius,
                this->slices,
                this->stacks);
}


void Torus::draw(){
    glutSolidTorus(this->inner,
                   this->outer,
                   this->slices, this->loops);
}


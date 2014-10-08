//
//  Primitives.cpp
//  CGFExample
//
//  Created by José Melo on 07/10/14.
//  Copyright (c) 2014 me. All rights reserved.
//

#include "Primitives.h"


void Rectangle::draw(){

    glBegin(GL_QUADS);
    
    glTexCoord2d(0,0);
    glVertex3d(x1,y1,0);
    glTexCoord2d(1,0);
    glVertex3d(x2,y1,0);
    glTexCoord2d(1,1);
    glVertex3d(x2,y2,0);
    glTexCoord2d(0,1);
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


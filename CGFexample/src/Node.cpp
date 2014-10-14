#include "Node.h"

void Node::draw(GLfloat previousMatrix[4][4]){
    
    //cout << "Drawing: " << this->getID() << endl;
    
    glLoadIdentity();
    glMultMatrixf(*previousMatrix);
    glMultMatrixf(*this->matrix);
    
    GLfloat multipliedMatrix[4][4];
    glGetFloatv(GL_MODELVIEW_MATRIX, &multipliedMatrix[0][0]);
    
    for(int i = 0; i < primitives->size(); i++){
        //cout << primitives->at(i)->getType() << endl;
        primitives->at(i)->draw();
    }
    
    if(descendants)
    {
        map<std::string,Node*>::iterator descendant=this->descendants->begin();
        for(int j= 0; j < this->descendants->size(); j++,descendant++){
            descendant->second->draw(multipliedMatrix);
        }
    }
    
}

void Node::calculateMatrix()
{
    glPushMatrix();
    
    glLoadIdentity();
    
    for(int j = 0; j < transforms->size(); j++){
        transforms->at(j)->apply();
    }
    
    glGetFloatv(GL_MODELVIEW_MATRIX, &matrix[0][0]);
    
    

    glPopMatrix();
}
#include "Node.h"

void Node::draw(GLfloat previousMatrix[4][4]){
    glLoadIdentity();
    glMultMatrixf(*previousMatrix);
    glMultMatrixf(*this->matrix);
    
    GLfloat multipliedMatrix[4][4];
    glGetFloatv(GL_MODELVIEW_MATRIX, &multipliedMatrix[0][0]);
    
    for(int i = 0; i < primitives->size(); i++){
        //cout << primitives->at(i)->getType() << endl;
        appearance->apply();
        primitives->at(i)->draw();
    }
    
    if(descendants)
    {
        map<std::string,Node*>::iterator descendant=this->descendants->begin();
        for(int j= 0; j < this->descendants->size(); j++,descendant++){
            appearance->apply();
            descendant->second->draw(multipliedMatrix, appearance);
        }
    }

}


void Node::draw(GLfloat previousMatrix[4][4], Appearance * previousAppearance){
    
    //cout << "Drawing: " << this->getID() << endl;
    if(strcmp(apperanceref.c_str(), "inherit")==0){
        appearance = previousAppearance;
    }
    
    glLoadIdentity();
    glMultMatrixf(*previousMatrix);
    glMultMatrixf(*this->matrix);
    
    GLfloat multipliedMatrix[4][4];
    glGetFloatv(GL_MODELVIEW_MATRIX, &multipliedMatrix[0][0]);
    
    for(int i = 0; i < primitives->size(); i++){
        //cout << primitives->at(i)->getType() << endl;
        appearance->apply();
        primitives->at(i)->draw();
    }
    
    if(descendants)
    {
        map<std::string,Node*>::iterator descendant=this->descendants->begin();
        for(int j= 0; j < this->descendants->size(); j++,descendant++){
            appearance->apply();
            descendant->second->draw(multipliedMatrix, appearance);
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
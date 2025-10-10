#include "Character.h"
// silence deprecation
#define GL_SILENCE_DEPRECATION
Character::Character(float pivotX, float pivotY, float charWidth, float charHeight){
        this -> pivotX = pivotX;

        this -> pivotY = pivotY;

        this -> charWidth = charWidth;

        this -> charHeight = charHeight;
}

// convert point pos into global pos
Point Character::convertPointPos(Point vertice){
    Point newPoint(0, 0);
            
    // get enum values
    float globalWidth = glutGet(GLUT_WINDOW_WIDTH);

    float globalHeight = glutGet(GLUT_WINDOW_HEIGHT);
            
    // translate relative pos into global pos
    newPoint.xPos = pivotX + (vertice.xPos * charWidth / 2) / (globalWidth / 2);

    newPoint.yPos = pivotY + (vertice.yPos * charHeight / 2) / (globalHeight / 2);

    return newPoint;
}

// add points to list
void Character::addVertex(Point vertex){
    vertices.push_back(vertex);
};


#ifndef DRAW_H
#define DRAW_H

#include <GLUT/glut.h>
#include "Character.h"
#include "Point.h"

void drawL();
    
void drawB();
   
void drawMainButton(bool isPressed);
   
void drawText(const char* text, float x, float y);
   
void drawDebugVertices(float x, float y);

void drawDebugVertices(const std::vector<Point>& vertices);
    
void drawStar(std::vector<Point>& verticesToBeMoved);

#endif
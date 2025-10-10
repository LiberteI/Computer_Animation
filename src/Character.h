#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <GLUT/glut.h>
#include "Point.h"
class Character{
    public:
        // field pivot x
        float pivotX;
        // pivot y
        float pivotY;
        // character max width
        float charWidth;
        // character max height
        float charHeight;

        // define vertice list (in a clock wise manner)
        std::vector<Point> vertices;

        // constructor
        Character(float pivotX, float pivotY, float charWidth, float charHeight);
            
        // convert point pos into global pos
        Point convertPointPos(Point vertice);
            

        // add points to list
        void addVertex(Point vertex);
           
};
#endif
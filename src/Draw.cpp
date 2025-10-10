#include "Shape.h"
#include "Draw.h"
void drawL(){
    // green
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_POLYGON);
        for(int i = 0; i < letterL.vertices.size(); i ++){
            glVertex2f(letterL.vertices[i].xPos, letterL.vertices[i].yPos);
        }
    glEnd();
}
    
void drawB(){
    // green
    glColor3f(0.0f, 1.0f, 0.0f);
    
    // draw
    glBegin(GL_POLYGON);
        for(int i = 0; i < outerLetterB.vertices.size(); i ++){
            glVertex2f(outerLetterB.vertices[i].xPos, outerLetterB.vertices[i].yPos);
        }
    glEnd();

   
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // draw
    glBegin(GL_POLYGON);
        for(int i = 0; i < innerLetterB_1.vertices.size(); i ++){
            glVertex2f(innerLetterB_1.vertices[i].xPos, innerLetterB_1.vertices[i].yPos);
        }
    glEnd();

    glBegin(GL_POLYGON);
        for(int i = 0; i < innerLetterB_2.vertices.size(); i ++){
            glVertex2f(innerLetterB_2.vertices[i].xPos, innerLetterB_2.vertices[i].yPos);
        }
    glEnd();
}
void drawMainButton(bool isPressed){
    // darker green
    glColor3f(0.0f, 0.5f, 0.0f);

    glBegin(GL_POLYGON);
        for(int i = 4; i < 8; i++){
            glVertex2f(mainButton.vertices[i].xPos, mainButton.vertices[i].yPos);
        }
    glEnd();
    
    float greenShader = 0;
    if(isPressed){
        greenShader = 0.2f;
    }
    else{
        greenShader = 0.8f;
    }
    // green
    glColor3f(0.0f, greenShader, 0.0f);

    glBegin(GL_POLYGON);
        for(int i = 0; i < 4; i++){
            glVertex2f(mainButton.vertices[i].xPos, mainButton.vertices[i].yPos);
        }
    glEnd();
}

void drawText(const char* text, float x, float y){
    glColor3f(1.0f, 0, 0);
    // use openGL coordinate system
    glRasterPos2f(x, y);

    // choose a glut built-in font
    for(const char* c = text; *c != '\0'; c ++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}
void drawDebugVertices(float x, float y){
    glColor3f(1.0f, 0, 0);

    glPointSize(6.0f);

    glBegin(GL_POINTS);

        glVertex2f(x, y);
    glEnd();
}

void drawDebugVertices(const std::vector<Point>& vertices) {
    glColor3f(1.0f, 0.0f, 0.0f);   

    glPointSize(6.0f);             
    
    glBegin(GL_POINTS);
    for (int i = 0; i < vertices.size(); i ++) {
        glVertex2f(vertices[i].xPos, vertices[i].yPos);
    }
    glEnd();
}

void drawStar(std::vector<Point>& verticesToBeMoved){
    for(int i = 0; i < 10; i ++){
        // green
        glColor3f(0.0f, 1.0f, 0.0f);

        // draw 10 triangles using the 1st i+1 i+2 vertex
        glBegin(GL_TRIANGLES);
            // get 1st
            float pivotX = verticesToBeMoved[0].xPos;
            float pivotY = verticesToBeMoved[0].yPos;

            // get i + 1
            float xi1 = verticesToBeMoved[i + 1].xPos;
            float yi1 = verticesToBeMoved[i + 1].yPos;

            // get i + 2
            // normally i + 2, for the last one, use 2nd to enclose the shape
            float xi2 = 0;
            float yi2 = 0;
            if(i + 1 == 10){
                xi2 = verticesToBeMoved[1].xPos;
                yi2 = verticesToBeMoved[1].yPos;
            }
            else{
                xi2 = verticesToBeMoved[i + 2].xPos;
                yi2 = verticesToBeMoved[i + 2].yPos;
            }
            
            // draw
            glVertex2f(pivotX, pivotY);
            glVertex2f(xi1, yi1);
            glVertex2f(xi2, yi2);
        glEnd();
    }
}

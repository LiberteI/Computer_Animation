#include "Character.h"
#include "Shape.h"

Character letterL(-0.5f, 0.0f, 300.0f, 300.0f);

Character outerLetterB(0.5f, 0.0f, 300.0f, 300.0f);

Character innerLetterB_1(0.5f, 0.0f, 300.0f, 300.0f);

Character innerLetterB_2(0.5f, 0.0f, 300.0f, 300.0f);

Character starLeft(-0.5f, 0.0f, 300.0f, 300.0f);

Character starRight(0.5f, 0.0f, 300.0f, 300.0f);

Character mainButton(0.0f, -0.7f, 60.0f, 60.0f);

// -------------- load --------------
void loadLeftStarVertices(){
    // pivot point
    Point p0 (0, 0);
    // initialise points starting from bottom left cornor;
    Point p1 (-0.4f, -0.6f);
    Point p2 ( 0.0f, -0.3f);
    Point p3 ( 0.4f, -0.6f);
    Point p4 ( 0.3f, -0.1f);
    Point p5 ( 0.7f,  0.2f);
    Point p6 ( 0.2f,  0.2f);
    Point p7 ( 0.0f,  0.7f);
    Point p8 (-0.2f,  0.2f);
    Point p9 (-0.7f,  0.2f);
    Point p10(-0.3f, -0.1f);

    // add vertices to char
    starLeft.addVertex(starLeft.convertPointPos(p0));
    starLeft.addVertex(starLeft.convertPointPos(p1));
    starLeft.addVertex(starLeft.convertPointPos(p2));
    starLeft.addVertex(starLeft.convertPointPos(p3));
    starLeft.addVertex(starLeft.convertPointPos(p4));
    starLeft.addVertex(starLeft.convertPointPos(p5));
    starLeft.addVertex(starLeft.convertPointPos(p6));
    starLeft.addVertex(starLeft.convertPointPos(p7));
    starLeft.addVertex(starLeft.convertPointPos(p8));
    starLeft.addVertex(starLeft.convertPointPos(p9));
    starLeft.addVertex(starLeft.convertPointPos(p10));
}
void loadRightStarVertices() {
    // pivot point
    Point p0 (0, 0);

    Point p1 (-0.4f, -0.6f);
    Point p2 ( 0.0f, -0.3f);
    Point p3 ( 0.4f, -0.6f);
    Point p4 ( 0.3f, -0.1f);
    Point p5 ( 0.7f,  0.2f);
    Point p6 ( 0.2f,  0.2f);
    Point p7 ( 0.0f,  0.7f);
    Point p8 (-0.2f,  0.2f);
    Point p9 (-0.7f,  0.2f);
    Point p10(-0.3f, -0.1f);

    starRight.addVertex(starRight.convertPointPos(p0));
    starRight.addVertex(starRight.convertPointPos(p1));
    starRight.addVertex(starRight.convertPointPos(p2));
    starRight.addVertex(starRight.convertPointPos(p3));
    starRight.addVertex(starRight.convertPointPos(p4));
    starRight.addVertex(starRight.convertPointPos(p5));
    starRight.addVertex(starRight.convertPointPos(p6));
    starRight.addVertex(starRight.convertPointPos(p7));
    starRight.addVertex(starRight.convertPointPos(p8));
    starRight.addVertex(starRight.convertPointPos(p9));
    starRight.addVertex(starRight.convertPointPos(p10));
}

// load vertices for l
void loadLVertices(){  
    // load in a clock wise manner from left bottom
    Point point1(-0.75, -1);
    // add point to L
    letterL.addVertex(letterL.convertPointPos(point1));

    // top left
    Point point2(-0.75, 1);
    // add point to L
    letterL.addVertex(letterL.convertPointPos(point2));

    // next to top left
    Point point3(-0.5, 1);
    // add point to L
    letterL.addVertex(letterL.convertPointPos(point3));

    // go down
    Point point4(-0.5, -0.7);
    // add point to L
    letterL.addVertex(letterL.convertPointPos(point4));

    // right
    Point point5(0.75, -0.7);
    // add point to L
    letterL.addVertex(letterL.convertPointPos(point5));

    // buttom right
    Point point6(0.75, -1);
    // add point to L
    letterL.addVertex(letterL.convertPointPos(point6));
}

// draw letter B
void defineCircle(Character& character, int segment, float radius, int posToPivot){
    // define circle of B using calculus
   
    for(int i = 0; i < segment; i++){
        // angle
        float theta = M_PI / segment * i;

        // current x pos
        float xPos = sinf(theta) * radius;

        // current y pos
        float yPos = cosf(theta) * radius + 0.5 * posToPivot;

        // take p poses
        Point p(xPos, yPos);
        // add to letter
        character.addVertex(character.convertPointPos(p));
    }
}
void loadOuterBVertices(){
    // bottom left
    Point p1(-1, -1);
    outerLetterB.addVertex(outerLetterB.convertPointPos(p1));

    // top left
    Point p2(-1, 1);
    outerLetterB.addVertex(outerLetterB.convertPointPos(p2));

    // draw 2 half circles
    defineCircle(outerLetterB, 50, 0.5, 1);

    defineCircle(outerLetterB, 50, 0.5, -1);

}
void loadInnerB1Vertices(){
    // bottom left
    Point p1(-0.75, -0.75);
    innerLetterB_1.addVertex(innerLetterB_1.convertPointPos(p1));

    // top left
    Point p2(-0.75, -0.25);
    innerLetterB_1.addVertex(innerLetterB_1.convertPointPos(p2));

    // draw half circle
    defineCircle(innerLetterB_1, 50, 0.25, -1);    
}
void loadInnerB2Vertices(){
    // bottom left
    Point p1(-0.75, 0.25);
    innerLetterB_2.addVertex(innerLetterB_2.convertPointPos(p1));

    // top left
    Point p2(-0.75, 0.75);
    innerLetterB_2.addVertex(innerLetterB_2.convertPointPos(p2));

    // draw half circle
    defineCircle(innerLetterB_2, 50, 0.25, 1);    
}

void loadMainButtonVertices(){
    // top layer
    Point p1(-1, 1);
    Point p2(0.75, 1);
    Point p3(0.75, -0.75);
    Point p4(-1, -0.75);

    mainButton.addVertex(mainButton.convertPointPos(p1));
    mainButton.addVertex(mainButton.convertPointPos(p2));
    mainButton.addVertex(mainButton.convertPointPos(p3));
    mainButton.addVertex(mainButton.convertPointPos(p4));

    // bottom layer
    Point p5(-1, 1);
    Point p6(1, 1);
    Point p7(1, -1);
    Point p8(-1, -1);

    mainButton.addVertex(mainButton.convertPointPos(p5));
    mainButton.addVertex(mainButton.convertPointPos(p6));
    mainButton.addVertex(mainButton.convertPointPos(p7));
    mainButton.addVertex(mainButton.convertPointPos(p8));
}

void initialShapes(){
    // load l vertices
    loadLVertices();

    // load outer B
    loadOuterBVertices();

    // rip inner B out
    loadInnerB1Vertices();

    loadInnerB2Vertices();

    // initial targets
    loadLeftStarVertices();
    loadRightStarVertices();

    loadMainButtonVertices();
}
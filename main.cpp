// silence deprecation
#define GL_SILENCE_DEPRECATION

// use GLUT library
#include <GLUT/glut.h>

#include <vector>
/*  
    task 2: morphing.

    1. define target star shape:
        1). index starts from left bottom vertex. 0 - 9
        2). calculate total perimeter and divide it into 10 parts.
    2. for shapes we already have.
        1). calculate total perimeter
        2). start counting vertex from bottom left cornor. use a clock-wise order to:
        3). define a new vertex every time we reach 10% of the total perimeter. 
    3. map vertices by index
*/
/*  
    task 1: draw a character

    1. define a pivot of the character.

    2. take dynamic numbers of points(struct) as vertices of such char.

    3. points' position are related to pivot.

    4. points are declared in a clock-wise order

    5. for character with a hollow hole: draw a hole with bg color
*/


struct Point{
    /*
        define: pos is related to pivot

        pivot is (0,0)

        -1 <= pos <= 1
    */
    public:
        float xPos, yPos;

    // constructor
    Point(float x, float y){
        xPos = x;
        yPos = y;
    }
};

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
        Character(float pivotX, float pivotY, float charWidth, float charHeight){
            this -> pivotX = pivotX;

            this -> pivotY = pivotY;

            this -> charWidth = charWidth;

            this -> charHeight = charHeight;
        }
        // convert point pos into global pos
        Point convertPointPos(Point vertice){
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
        void addVertex(Point vertex){
            vertices.push_back(vertex);
        };
};
// declare letters after class definations as global variables
Character letterL(-0.5f, 0.0f, 300.0f, 300.0f);

Character outerLetterB(0.5f, 0.0f, 300.0f, 300.0f);

Character innerLetterB_1(0.5f, 0.0f, 300.0f, 300.0f);

Character innerLetterB_2(0.5f, 0.0f, 300.0f, 300.0f);

Character starLeft(-0.5f, 0.0f, 300.0f, 300.0f);

Character starRight(0.5f, 0.0f, 300.0f, 300.0f);

Character mainButton(0.0f, -0.7f, 60.0f, 60.0f);

bool hasMorphed = false;

bool isMorphing = false;

// interpolation progress from 0 to 1
float morphT = 0.0f;

bool buttonDown;

std::vector<Point> verticesOfL;
std::vector<Point> verticesOfB;

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
        glBegin(GL_TRIANGLES);
            float pivotX = verticesToBeMoved[0].xPos;
            float pivotY = verticesToBeMoved[0].yPos;

            float xi1 = verticesToBeMoved[i + 1].xPos;
            float yi1 = verticesToBeMoved[i + 1].yPos;

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
    
            glVertex2f(pivotX, pivotY);
            glVertex2f(xi1, yi1);
            glVertex2f(xi2, yi2);
        glEnd();
    }
}
void morphShape(std::vector<Point> startShapeVertices, std::vector<Point> targetShapeVertices){
    
    std::vector<Point> verticesToBeMoved = startShapeVertices;
    
    // map x y values by index
    for (int i = 0; i < 11; i++) {
        float startX = startShapeVertices[i].xPos;
        float startY = startShapeVertices[i].yPos;

        float targetX = targetShapeVertices[i].xPos;
        float targetY = targetShapeVertices[i].yPos;

        // proper LERP interpolation
        verticesToBeMoved[i].xPos = startX + morphT * (targetX - startX);
        verticesToBeMoved[i].yPos = startY + morphT * (targetY - startY);

    }    
    drawDebugVertices(verticesToBeMoved);
    drawStar(verticesToBeMoved);
    
}

// helper method for computing distance between 2 points in the global scope.
float dist(Point a, Point b){
    float deltaX = a.xPos - b.xPos;
    float deltaY = a.yPos - b.yPos;

    return sqrt(deltaX * deltaX + deltaY * deltaY);
}

// helper method: for calculating the perimeter of a shape before morphing
float calculateMaxPerimeter(const Character& shape){
    // resample
    
    // calculate max perimeter.
    float maxPerimeter = 0;
    
    Point prevPoint(shape.vertices[0].xPos, shape.vertices[0].yPos);

    for(int i = 0; i < shape.vertices.size(); i ++){
        Point curPoint = shape.vertices[i];

        float curDist = dist(prevPoint, curPoint);

        prevPoint = curPoint;

        maxPerimeter += curDist;
    }

    maxPerimeter += dist(shape.vertices[0], shape.vertices[shape.vertices.size() - 1]);

    return maxPerimeter;
}
/*
        Resample the input shape into 11 evenly spaced vertices 
        along its perimeter using distance accumulation and interpolation.

        Algorithm Overview:
        --------------------
        1.  Compute the total perimeter of the shape.

        2.  Calculate the threshold distance between samples:
            threshold = totalPerimeter / 11.0f

        3.  Start walking along the shape’s edges (from vertex[i] to vertex[i+1]):
            - Keep track of how far we’ve walked (accumulatedDis).
            - When accumulatedDis + currentSegmentLength < threshold:
                → move to the next edge and continue accumulating distance.

        4.  When accumulatedDis + currentSegmentLength >= threshold:
            - The next sample lies somewhere *along this segment*.
            - Compute the exact interpolation ratio:
                    t = (threshold - accumulatedDis) / currentSegmentLength
            - Create a new vertex at that position:
                    newVertex = start + t * (end - start)
            - Reset accumulatedDis = 0, 
              and continue walking from this new vertex.

        5.  Repeat until 11 new vertices have been generated.

        Notes:
        ------
        • Ensures evenly spaced vertices around the perimeter.
        • Keeps the same vertex order (clockwise or counterclockwise).
        • Works for any closed polygon (convex or concave).
        • No need for artificial "50-step" subdivisions — 
        the interpolation computes exact positions mathematically.
    */


// lil helper for resampling
Point interpolate(Point& curPoint, Point& nextPoint, float t){
    // compute delta x y to interpolate
    float deltaX = nextPoint.xPos - curPoint.xPos;

    float deltaY = nextPoint.yPos - curPoint.yPos;

    Point newPoint = curPoint;

    newPoint.xPos = curPoint.xPos + deltaX * t;

    newPoint.yPos = curPoint.yPos + deltaY * t;

    return newPoint;
}

std::vector<Point> resample(Character& shape){
    // define new vertices list and keep track of its element count;
    std::vector<Point> newVertices;
    // compute total perimeter
    float totalPerimeter = calculateMaxPerimeter(shape);
    float threshold = totalPerimeter / 11.0f;
    // define accumulated distance (perimeter / 11 threshold), get emptied once accumulated dist >= threshold
    float accumulatedDis = 0;
    int curIdx = 0;
    // the initial point is the pivot of the star
    newVertices.push_back(shape.vertices[0]);
    Point curVertex = shape.vertices[curIdx];
    while(newVertices.size() < 11){
        int nextIdx = curIdx + 1;
        // calculate the distance from this point to next point
        float segmentLength = dist(shape.vertices[curIdx], shape.vertices[nextIdx]);
        // keep track of curPoint position and accumulated distance
        // scan
        if(accumulatedDis + segmentLength < threshold){
            // scan the next vertex, the distance does not exceed threshold, then skip.
            accumulatedDis += segmentLength;

            // set where we are to cur Point
            curVertex = shape.vertices[curIdx];
            curIdx ++;
        }
        // interpolation
        else{
            float remain = threshold - accumulatedDis;

            float t = remain / segmentLength;
            if(newVertices.size() == 10){
                curVertex = interpolate(shape.vertices[curIdx], newVertices[0], t);
                newVertices.push_back(curVertex);
                break;
            }
            // break down the distance between these points using interpolation
            curVertex = interpolate(shape.vertices[curIdx], shape.vertices[nextIdx], t);
            newVertices.push_back(curVertex);
            accumulatedDis = 0;
            shape.vertices[curIdx] = curVertex;
            
        }
    }
    return newVertices;
}


void morphTimer(int value){
    if(isMorphing){
        // morph speed
        morphT += 0.02f;

        // done
        if(morphT >= 1.0f){
            morphT = 1.0f;
            isMorphing = false;
        }

        // request redraw myDisplay
        glutPostRedisplay();

        // call morphTimer every 16 milliseconds
        glutTimerFunc(16, morphTimer, 0);
    }
}

bool isInClickableArea(int x, int y){
    int totalWidth = glutGet(GLUT_WINDOW_WIDTH);

    int totalHeight = glutGet(GLUT_WINDOW_HEIGHT);

    int buttonLeftBound = totalWidth / 2 - mainButton.charWidth / 2;
    int buttonRightBound = totalWidth / 2 + mainButton.charWidth / 2;

    int buttonBottomBound = totalHeight - (int)(0.15f * totalHeight) + mainButton.charHeight / 2;

    int buttonTopBound = buttonBottomBound - mainButton.charHeight;

    return x > buttonLeftBound && x < buttonRightBound && y > buttonTopBound && y < buttonBottomBound;

}
void onMouseClick(int button, int state, int x, int y){
    
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(!isInClickableArea(x, y)){
            printf("you did not reach the button\n");

            return;
        }
        // printf("left button got pressed at %d, %d\n", x, y);
        // for the time being, do morphing once clicked.
        buttonDown = true;
        if(!hasMorphed){
            // startMorphing();
            // resample L
            verticesOfL = resample(letterL);

            // resample B
            verticesOfB = resample(outerLetterB);
            hasMorphed = true;
            isMorphing = true;
            
        }
        
        glutTimerFunc(0, morphTimer, 0);
        // if button region gets clicked, then play button animation
    } 
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        // printf("left button got released at %d, %d\n", x, y);
        // if button region gets released, recover button.
        buttonDown = false;
    }
}

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    drawMainButton(buttonDown);

    drawText("Morph", mainButton.pivotX - 0.05f, mainButton.pivotY);

    if(!isMorphing && !hasMorphed){
        drawL();
        
        drawB();
    }
    else if(isMorphing || hasMorphed){
        glColor3f(0.0f, 1.0f, 0.0f);

        morphShape(verticesOfL, starLeft.vertices);

        morphShape(verticesOfB, starRight.vertices);
    }

    
    glutSwapBuffers();
}

void idleCallBack(){
    glutPostRedisplay();
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
int main(int argc, char** argv){
    // initialise GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // default size of 300 * 300 pixels but initialise it 800 * 600
    glutInitWindowSize(800, 600);

    // create a window named "Assignment_1"
    glutCreateWindow("Assignment_1");

    // register on click
    glutMouseFunc(onMouseClick);

    // load vertices of shapes
    initialShapes();

    // execute callback
    glutDisplayFunc(myDisplay);

    // ensure button still works after morphing
    glutIdleFunc(idleCallBack);

    // start glut state machine
    glutMainLoop();
    return 0;
}
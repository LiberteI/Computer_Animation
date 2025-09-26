// silence deprecation
#define GL_SILENCE_DEPRECATION

// use GLUT library
#include <GLUT/glut.h>

#include <vector>
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

Character innerLetterB(0.5f, 0.0f, 300.0f, 300.0f);
// class Button{
//     public:
//         int pivotX;

//         int pivotY;

//         int buttonWidth;

//         int buttonLength;

// };

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
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);        // filled circle
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(cx, cy);              // center
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments); // angle
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
void defineCircle(Character& character, int segment, float radius, int posToPivot){
    // define circle of B using calculus
   
    for(int i = 0; i < segment; i++){
        // angle
        float theta = M_PI / segment * i;

        // current x pos
        float xPos = sinf(theta) * radius;

        // current y pos
        float yPos = cosf(theta) * radius + radius * posToPivot;

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

    defineCircle(outerLetterB, 50, 0.5, 1);

    defineCircle(outerLetterB, 50, 0.5, -1);

}

void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    // green
    glColor3f(0.0f, 1.0f, 0.0f);

    // load l vertices
    loadLVertices();
    
    glBegin(GL_POLYGON);
        for(int i = 0; i < letterL.vertices.size(); i ++){
            glVertex2f(letterL.vertices[i].xPos, letterL.vertices[i].yPos);
        }
    glEnd();
    
    // draw pivots
    drawCircle(outerLetterB.pivotX, outerLetterB.pivotY, 0.05, 50);
    
    // green
    glColor3f(0.0f, 1.0f, 0.0f);
    // load outer B
    loadOuterBVertices();

    // draw
    glBegin(GL_POLYGON);
        for(int i = 0; i < outerLetterB.vertices.size(); i ++){
            glVertex2f(outerLetterB.vertices[i].xPos, outerLetterB.vertices[i].yPos);
        }
    glEnd();

    glFlush();
}
int main(int argc, char** argv){
    // initialise GLUT
    glutInit(&argc, argv);

    // default size of 300 * 300 pixels but initialise it 800 * 600
    glutInitWindowSize(800, 600);

    // create a window named "Assignment_1"
    glutCreateWindow("Assignment_1");

    // execute callback
    glutDisplayFunc(myDisplay);

    // start glut state machine
    glutMainLoop();
    return 0;
}
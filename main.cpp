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
            Point newPoint;
            
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
Character letterL(-0.5f, 0.0f, 250.0f, 100.0f);

Character letterB(0.5f, 0.0f, 250.0f, 100.0f);


class Button{
    public:
        int pivotX;

        int pivotY;

        int buttonWidth;

        int buttonLength;

};

void loadLVertices(){
    
}
void myDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);

    // green
    glColor3f(0.0f, 1.0f, 0.0f);
    // draw pivots
    glBegin(GL_LINES);
        glVertex2f(letterL.pivotX, letterL.pivotY);
        glVertex2f(letterB.pivotX, letterB.pivotY);
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
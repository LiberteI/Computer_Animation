// silence deprecation
#define GL_SILENCE_DEPRECATION

// use GLUT library
#include <GLUT/glut.h>

#include <vector>

#include "Character.h"

#include "Draw.h"

#include "Shape.h"

#include "Morph.h"
/*  
    task 2: morphing.

    1. define target star shape:
        1). index starts from left bottom vertex. 0 - 10
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

bool isInClickableArea(int x, int y){
    int totalWidth = glutGet(GLUT_WINDOW_WIDTH);

    int totalHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // calculate bounds in x axis
    int buttonLeftBound = totalWidth / 2 - mainButton.charWidth / 2;
    int buttonRightBound = totalWidth / 2 + mainButton.charWidth / 2;

    // calculate bounds in y axis
    int buttonBottomBound = totalHeight - (int)(0.15f * totalHeight) + mainButton.charHeight / 2;
    int buttonTopBound = buttonBottomBound - mainButton.charHeight;

    // valid area should be the button box
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
            resampledVerticesOfL = resample(letterL);

            // resample B
            resampledVerticesOfB = resample(outerLetterB);
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

        morphShape(resampledVerticesOfL, starLeft.vertices);

        morphShape(resampledVerticesOfB, starRight.vertices);
    }

    
    glutSwapBuffers();
}

void idleCallBack(){
    // request re-display using idle function
    glutPostRedisplay();
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
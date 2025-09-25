// silence deprecation
#define GL_SILENCE_DEPRECATION

// use GLUT library
#include <GLUT/glut.h>


void display(){
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // red
    glColor3f(1.0, 0.0, 0.0);

    // draw a square, use begin to declare a drawing
    glBegin(GL_POLYGON);

    // define 4 points
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5f);
    glVertex2f(0.5, 0.5f);
    glVertex2f(-0.5f, 0.5f);

    // mark glBegin end
    glEnd();

    // enforce drawing
    glFlush();

}
int main(int argc, char** argv){
    // initialise GLUT
    glutInit(&argc, argv);

    // create a window
    glutCreateWindow("Hello OpenGL!");

    // register display function
    glutDisplayFunc(display);

    // start loop
    glutMainLoop();
    return 0;
}
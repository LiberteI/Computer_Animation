#ifndef POINT_H
#define POINT_H
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
#endif

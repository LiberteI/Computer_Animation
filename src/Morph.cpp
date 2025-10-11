#include <vector>

#include "Morph.h"

#include "Draw.h"

#include "Shape.h"

#define GL_SILENCE_DEPRECATION
bool hasMorphed = false;

bool isMorphing = false;

// interpolation progress from 0 to 1
float morphT = 0.0f;

bool buttonDown;

std::vector<Point> resampledVerticesOfL;
std::vector<Point> resampledVerticesOfB;


// ------------------ morph ----------------
void morphShape(std::vector<Point> startShapeVertices, std::vector<Point> targetShapeVertices){
    
    // copy in-process vertices
    std::vector<Point> verticesToBeMoved = startShapeVertices;
    
    // map x y values by index
    for (int i = 0; i < 11; i++) {
        // define start point and target point
        float startX = startShapeVertices[i].xPos;
        float startY = startShapeVertices[i].yPos;

        float targetX = targetShapeVertices[i].xPos;
        float targetY = targetShapeVertices[i].yPos;

        // proper LERP interpolation
        verticesToBeMoved[i].xPos = startX + morphT * (targetX - startX);
        verticesToBeMoved[i].yPos = startY + morphT * (targetY - startY);

    }    
    // show resampled vertices using debug method
    drawDebugVertices(verticesToBeMoved);

    // draw star while being moved
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
    
    // define last point
    Point prevPoint(shape.vertices[0].xPos, shape.vertices[0].yPos);

    for(int i = 0; i < shape.vertices.size(); i ++){
        // get next vertex
        Point curPoint = shape.vertices[i];

        // get dist
        float curDist = dist(prevPoint, curPoint);

        // update point
        prevPoint = curPoint;

        // increment
        maxPerimeter += curDist;
    }

    // sum up
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
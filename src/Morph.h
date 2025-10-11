#ifndef MORPH_H

#define MORPH_H

#include <vector>

#include "Character.h"

extern bool hasMorphed;

extern bool isMorphing;

extern float morphT;

extern bool buttonDown;

extern std::vector<Point> resampledVerticesOfL;
extern std::vector<Point> resampledVerticesOfB;

void morphShape(std::vector<Point> startShapeVertices, std::vector<Point> targetShapeVertices);

void morphTimer(int value);

float dist(Point a, Point b);

float calculateMaxPerimeter(const Character& shape);

Point interpolate(Point& curPoint, Point& nextPoint, float t);

std::vector<Point> resample(Character& shape);

#endif
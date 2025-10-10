#include "Character.h"
extern Character letterL;

extern Character outerLetterB;

extern Character innerLetterB_1;

extern Character innerLetterB_2;

extern Character starLeft;

extern Character starRight;

extern Character mainButton;

void loadLeftStarVertices();
void loadRightStarVertices();

// load vertices for l
void loadLVertices();

// draw letter B
void defineCircle(Character& character, int segment, float radius, int posToPivot);
void loadOuterBVertices();
void loadInnerB1Vertices();
void loadInnerB2Vertices();
void loadMainButtonVertices();

void initialShapes();
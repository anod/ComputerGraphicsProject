//
//  world.h
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/14/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#ifndef Home_Work_2_world_h
#define Home_Work_2_world_h

#include <math.h>
#include "ground.h"
#include "pixel.h"

static const int WIDTH = 600;
static const int HEIGHT = 600;


extern PIXEL pix[HEIGHT][WIDTH];
extern GROUND ground[HEIGHT][WIDTH];
extern PIXEL heightPixel[HEIGHT_RANGE];

void onGroundChange();
void setRoadLine(int x1, int y1, int x2, int y2);
void drawRoads();
void drawRoad(int x1, int y1, int x2, int y2);
void drawPixel(int x, int y, PIXEL color);
void drawHill(int x, int y);
void drawValley(int x,int y);
void drawColorLine(int x1, int y1, int x2, int y2, PIXEL color);
void drawSquare(int x1, int y1, int x2, int y2, PIXEL color);
void drawTree(int x,int y);
void fillSquare(int x1, int y1, int x2, int y2, PIXEL color);
PIXEL gradientPixel(PIXEL from, PIXEL to, int level, int maxLevel);
int gradientValue(int from, int to,int level, int maxLevel);
void worldInit();


#endif

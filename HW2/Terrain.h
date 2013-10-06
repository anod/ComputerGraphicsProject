//
//  terrain.h
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/21/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#ifndef Home_Work_2_terrain_h
#define Home_Work_2_terrain_h

#include <math.h>
#include <stdlib.h>     /* srand, rand */

static const int GRID_SIZE = 200;

extern double grid[GRID_SIZE][GRID_SIZE];

void terrainInit();
void terrainSmooth();
void terrainGenerate1();
void terrainGenerate2();
void terrainGenerate3();

#endif

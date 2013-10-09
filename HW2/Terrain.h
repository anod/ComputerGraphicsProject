//
//  Terrain.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include "glut.h"
#include "general.h"

class Terrain
{
public:
	Terrain::Terrain(void);
	Terrain::~Terrain(void);
	void init();
	virtual void draw3d();
	virtual void draw2d();

private:
	static const int GRID_SIZE = 200;
	double mGrid[GRID_SIZE][GRID_SIZE];

	void smooth();
	void generate1();
	void generate2();
	void generate3();
	void drawHeightColor(double h);
	void drawHeightColor2d(double h);
};
#endif

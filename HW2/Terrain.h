//
//  Terrain.h
//  Home Work 2
//
//  Created by Alex Gavrishev on 8/21/13.
//  Copyright (c) 2013 Alex Gavrishev. All rights reserved.
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include "Drawable.h"
#include "glut.h"


class Terrain : public Drawable
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

	void draw();
	void smooth();
	void generate1();
	void generate2();
	void generate3();
	void drawHeightColor(double h);
};
#endif

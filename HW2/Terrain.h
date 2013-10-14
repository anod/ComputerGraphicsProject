//
//  Terrain.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include "general.h"

class Terrain
{
public:
	Terrain::Terrain(void);
	Terrain::~Terrain(void);
	void init();
	void drawHill(int x, int y);
	void drawValley(int x,int y);
	void draw3d();
	void draw2d();

private:
	static const int HILL_RADIUS = 7;//px
	static const int VALLEY_RAIUS = 7; //px

	double mGrid[GRID_SIZE][GRID_SIZE];

	void smooth();
	void generate1();
	void generate2();
	void generate3();
	void drawHeightColor(double h);
	void drawHeightColor2d(double h);
};
#endif

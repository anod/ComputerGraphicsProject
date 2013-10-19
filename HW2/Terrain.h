//
//  Terrain.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include "general.h"
#include "Road.h"

class Terrain
{
public:

	Terrain::Terrain(void);
	Terrain::~Terrain(void);
	void init(Road* road);
	void drawHill(int x, int y);
	void drawValley(int x,int y);
	void draw3d();
	void draw2d();
	void onRoadAdd(int x, int y);
	void ptToGrid(int pt);

private:
	static const int HILL_RADIUS = 7;//px
	static const int VALLEY_RAIUS = 7; //px

	Road* mRoad;
	double mGrid[GRID_SIZE][GRID_SIZE];

	void updateGrid(int x, int y, int height);
	void smooth();
	void generate1();
	void generate2();
	void generate3();
	void drawHeightColor(double h);
	void drawHeightColor2d(double h,bool isRoad,PIXEL roadColor);
};
#endif

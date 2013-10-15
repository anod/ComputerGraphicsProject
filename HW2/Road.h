//
//  Road.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef ROAD_H
#define ROAD_H

#include "general.h"
class Terrain;

class Road
{
public:
	Road(void);
	~Road(void);

	void init(Terrain* terrain);

	void add(int startX, int startY, int endX, int endY);
	void onTerrainUpdate(int i, int j, bool isWater);
private:
	Terrain* mTerrain;

	double mRoad[GRID_SIZE][GRID_SIZE];
	double mBridge[GRID_SIZE][GRID_SIZE];

	void addRoadPoints(int cx, int cy);
	void setBridgePoints(int cx, int cy, int value);
};

#endif

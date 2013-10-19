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
	bool isRoad(int i, int j) { 
		return mRoad[i][j] > 0; 
	};
	bool isBridge(int i, int j) {
		return mBridge[i][j] > 0;
	};
	void add(int startX, int startY, int endX, int endY);
	void onTerrainUpdate(int x, int y, bool isWater);
private:
	Terrain* mTerrain;

	double mRoad[GRID_SIZE][GRID_SIZE];
	double mBridge[GRID_SIZE][GRID_SIZE];

	void addRoadPoints(int cx, int cy);
	void setBridgePoints(int cx, int cy, int value);
};

#endif

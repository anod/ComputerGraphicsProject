//
//  Road.h
//  Final Project
//
//  Created by Alex Gavrishev.
//

#ifndef ROAD_H
#define ROAD_H

#include "general.h"
#include <vector>
class Terrain;

typedef struct
{
	int x1,y1,x2,y2;
} ROADPOINT;

// Store road information on the grid
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
	void rebuild();
	void build(int x1, int y1, int x2, int y2);
private:
	static const int ROAD_DRIVE = 1;//px
	static const int ROAD_SIDE = 2;//px
	Terrain* mTerrain;

	std::vector<ROADPOINT> mRoadPoints;
	double mRoad[GRID_SIZE][GRID_SIZE];
	double mBridge[GRID_SIZE][GRID_SIZE];

	void addRoadPoints(int cx, int cy, double p);
	void setBridgePoints(int cx, int cy, int value);
	void buildNotDirect(int x1, int y1, int x2, int y2);
	void clear();
};

#endif

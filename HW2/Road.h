//
//  Road.h
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#ifndef ROAD_H
#define ROAD_H

#include "general.h"

class Road
{
public:
	Road(void);
	~Road(void);
	void init();
	int[][] getRoad() { return mRoad; }
	void add(int startX, int startY, int endX, int endY);
private:
	double mRoad[GRID_SIZE][GRID_SIZE];

	void addRoadPoints(int cx, int cy);

};

#endif

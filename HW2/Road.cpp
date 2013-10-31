//
//  Road.cpp
//  Home Work 2
//
//  Created by Alex Gavrishev.
//

#include "Road.h"
#include "Terrain.h"

Road::Road(void)
{

}


Road::~Road(void)
{
}

void Road::init(Terrain* terrain) {

	mTerrain = terrain;

	clear();

}

void Road::clear() {
	for(int i=0;i<GRID_SIZE;i++) {
		for(int j=0;j<GRID_SIZE;j++)
		{
			mRoad[i][j] = 0;
			mBridge[i][j] = 0;
		}
	}
}

void Road::rebuild() {

	clear();
	for (std::vector<ROADPOINT>::iterator it = mRoadPoints.begin(); it != mRoadPoints.end(); ++it) {
		ROADPOINT point = *it;
		build(point.x1,point.y1,point.x2,point.y2);
	}
}

void Road::build(int x1, int y1, int x2, int y2) {
	double a,b,p;
	int x,y;
	int start,stop;
	int width = 2;

	if (x1==x2 && y1==y2) {
		return;
	}
	
	if (x2 == x1) {
		if (y1 > y2) {
			start = y2;
			stop = y1;
		} else {
			start = y1;
			stop = y2;
		}
		
		for(y = start; y <= stop; y++) {
			addRoadPoints(x1,y,0);
		}
		return;
	}
	
	a = (y2-y1)/double(x2-x1);
	p = -1.0f/a;
	b = y1 - a * x1;
	
	if (fabs(a)<=1)
	{
		if (x1 > x2) {
			start = x2;
			stop = x1;
		} else {
			start = x1;
			stop = x2;
		}
		
		for(x = start; x <= stop; x++) {
			y = a*x+b;
			addRoadPoints(x,y,p);
		}
	} else {
		if (y1 > y2) {
			start = y2;
			stop = y1;
		} else {
			start = y1;
			stop = y2;
		}
		
		for(y = start; y <= stop; y++) {
			x = (y-b)/a;
			addRoadPoints(x,y,p);
		}
	}
}

void Road::add(int x1, int y1, int x2, int y2) {
	ROADPOINT points = {x1, y1, x2, y2};
	mRoadPoints.push_back(points);
	rebuild();
}



void Road::addRoadPoints(int cx, int cy, double p) {
	int x0 = cx - 4;
	int x1 = cx + 4;
	x0 = (x0 < 0) ? 0 : x0;
	x1 = (x1 >= GRID_SIZE) ? GRID_SIZE : x1;
	int y0 = cy - 4;
	int y1 = cy + 4;
	y0 = (y0 < 0) ? 0 : y0;
	y1 = (y1 >= GRID_SIZE) ? GRID_SIZE : y1;
	

	bool isBridge = false;

	for (int i = x0; i < x1; i++) {
		for (int j = y0; j < y1; j++) {
			mRoad[j][i] = 1;
			if (mTerrain->isWater(i, j)) {
				isBridge = true;
				mBridge[j][i] = 1;
			}
			mTerrain->onRoadAdd(i,j);
		}
	}
	//update bridge info
	for (int i = x0; i < x1; i++) {
		for (int j = y0; j < y1; j++) {
			mBridge[j][i] = (isBridge) ? 1:0;
		}
	}

}
